#ifndef INNER_PROC_CLUSTER_H
#define	INNER_PROC_CLUSTER_H

#include "../BootServer/global.h"

#if defined(_WIN32) || defined(_WIN64)
#pragma comment(lib, "BootServer.lib")
#endif

#ifdef __cplusplus
extern "C" {
#endif

__declspec_dllexport int rpcReqClusterList(TaskThread_t* thrd, Cluster_t* sc_cluster);
__declspec_dllexport void distributeClusterList(TaskThread_t* thrd, UserMsg_t* ctrl);

#ifdef __cplusplus
}
#endif

#endif // !INNER_PROC_CLUSTER_H
