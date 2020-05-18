#ifndef CLUSTER_PROC_H
#define	CLUSTER_PROC_H

#include "../BootServer/global.h"

#if defined(_WIN32) || defined(_WIN64)
#pragma comment(lib, "BootServer.lib")
#endif

#ifdef __cplusplus
extern "C" {
#endif

__declspec_dllexport int callReqClusterList(int socktype, const char* ip, unsigned short port);
__declspec_dllexport void retClusterList(UserMsg_t* ctrl);

#ifdef __cplusplus
}
#endif

#endif // !CLUSTER_PROC_H
