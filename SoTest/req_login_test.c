#include "../BootServer/global.h"
#include "cmd.h"
#include "test_handler.h"
#include <stdio.h>

void reqLoginTest(UserMsg_t* ctrl) {
	cJSON* cjson_req_root;
	cJSON *cjson_ret_root;
	SendMsg_t ret_msg;
	char* ret_data;
	Cluster_t* cluster;
	int ok;

	cjson_req_root = cJSON_Parse(NULL, (char*)ctrl->data);
	if (!cjson_req_root) {
		fputs("cJSON_Parse", stderr);
		return;
	}
	printf("req: %s\n", (char*)(ctrl->data));

	ok = 0;
	do {
		cJSON* cjson_name, *cjson_ip, *cjson_port;

		cjson_name = cJSON_Field(cjson_req_root, "name");
		if (!cjson_name) {
			break;
		}
		cjson_ip = cJSON_Field(cjson_req_root, "ip");
		if (!cjson_ip) {
			break;
		}
		cjson_port = cJSON_Field(cjson_req_root, "port");
		if (!cjson_port) {
			break;
		}

		cluster = getCluster(cjson_name->valuestring, cjson_ip->valuestring, cjson_port->valueint);
		if (!cluster) {
			cluster = newCluster();
			if (!cluster) {
				break;
			}
			strcpy(cluster->ip, cjson_ip->valuestring);
			cluster->port = cjson_port->valueint;
			if (!regCluster(cjson_name->valuestring, cluster)) {
				freeCluster(cluster);
				channelSendv(ctrl->channel, NULL, 0, NETPACKET_FIN);
				fputs("regCluster", stderr);
				break;
			}
		}
		cluster->session.id = allocSessionId();
		sessionChannelReplaceServer(&cluster->session, ctrl->channel);
		ok = 1;
	} while (0);
	cJSON_Delete(cjson_req_root);
	if (!ok) {
		return;
	}

	cjson_ret_root = cJSON_NewObject(NULL);
	cJSON_AddNewNumber(cjson_ret_root, "session_id", cluster->session.id);
	ret_data = cJSON_Print(cjson_ret_root);
	cJSON_Delete(cjson_ret_root);

	makeSendMsg(&ret_msg, CMD_RET_LOGIN_TEST, ret_data, strlen(ret_data));
	channelSendv(ctrl->channel, ret_msg.iov, sizeof(ret_msg.iov) / sizeof(ret_msg.iov[0]), NETPACKET_FRAGMENT);
	free(ret_data);
}

void retLoginTest(UserMsg_t* ctrl) {
	cJSON* cjson_ret_root;

	cjson_ret_root = cJSON_Parse(NULL, (char*)ctrl->data);
	if (!cjson_ret_root) {
		fputs("cJSON_Parse", stderr);
		return;
	}

	do {
		cJSON* cjson_sessoin_id;

		cjson_sessoin_id = cJSON_Field(cjson_ret_root, "session_id");
		if (!cjson_sessoin_id) {
			fputs("miss session id field", stderr);
			break;
		}
		channelSessionId(ctrl->channel) = cjson_sessoin_id->valueint;
	} while (0);
	cJSON_Delete(cjson_ret_root);

	printf("ret: %s\n", (char*)ctrl->data);

	// test code
	if (ptr_g_RpcFiberCore())
		frpc_test_code(ctrl->channel);
	else if (ptr_g_RpcAsyncCore())
		arpc_test_code(ctrl->channel);
}