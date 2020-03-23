#ifndef MQ_CMD_H
#define	MQ_CMD_H

enum {
	CMD_REQ_RECONNECT = 1,
	CMD_RET_RECONNECT,

	CMD_REQ_UPLOAD_CLUSTER,
	CMD_RET_UPLOAD_CLUSTER,
	CMD_NOTIFY_NEW_CLUSTER,
	CMD_REQ_REMOVE_CLUSTER,
	CMD_RET_REMOVE_CLUSTER,

	RPC_CMD_START	= 10000,
	RPC_CMD_TEST	= 10001,
};

#endif // !MQ_CMD_H
