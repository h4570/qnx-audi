/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
#
# ============================================================
# Reversed comStack* private functions from Audi's libhybrid.so
# ============================================================
*/

#ifndef _QNX_AUDI_COM_STACK_P_
#define _QNX_AUDI_COM_STACK_P_

#include <pthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

    pthread_key_t COM_STACK_KEY;
    pthread_mutex_t COM_STACK_MUTEX;
    bool COM_STACK_IS_KEY_CREATED = false;

    void comStackClearThreadKey(void *data);
    int comStackOpen(const char *device);
    int comStackClose(const int fd);

#ifdef __cplusplus
}
#endif

#endif