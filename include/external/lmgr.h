/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
#
# ============================================================
# Reversed lmgr* functions from Audi's libhybrid.so
# ============================================================
*/

#ifndef _QNX_AUDI_LMGR_
#define _QNX_AUDI_LMGR_

#include "external/com_stack.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void lmgrCheckVersion();
    void lmgrRegisterDisplayable(int param1, unsigned int param2, unsigned int param3, int param4);
    void lmgrGetVfb(int param, int *sid);
    void lmgrUpdateVfb(int param);
    void lmgrTalkToLayerManager(int *inputData, int inputDataSize, int param3);

#ifdef __cplusplus
}
#endif

#endif