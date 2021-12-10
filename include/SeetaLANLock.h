#ifndef INC_SEETA_LAN_LOCK_H
#define INC_SEETA_LAN_LOCK_H
#include "seetaauthorize_export.h"

#ifdef __cplusplus
extern "C" {
#endif

//extern "C" SEETAAUTHORIZE_EXPORT void SeetaLock_SetServerAddress(const char *ip, int port);
struct SeetaLock_Function;
extern "C" SEETAAUTHORIZE_EXPORT void SeetaLock_call(SeetaLock_Function *function);

#ifdef __cplusplus
}
#endif

#endif // INC_SEETA_LAN_LOCK_H
