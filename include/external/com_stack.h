/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
#
# ============================================================
# Reversed comStack* functions from Audi's libhybrid.so
# ============================================================
*/

#ifndef _QNX_AUDI_COM_STACK_
#define _QNX_AUDI_COM_STACK_

#include <pthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void comStackConnect();
    void comStackDisconnect();
    void comStackSend(int dcmd, void *data, size_t dataBytes);

#ifdef __cplusplus
}
#endif

#endif