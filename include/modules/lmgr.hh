/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_LMGR_
#define _QNX_AUDI_LMGR_

#include "modules/com_stack.hh"

/** 
 * Class responsible for "lmgr" communication with Audi.
 * Contains reversed lmgr* functions from Audi's libhybrid.so
 */
class Lmgr
{

public:
    Lmgr(ComStack *comStack);
    ~Lmgr();

    // ----
    //  Other
    // ----

    void checkVersion();

    void registerDisplayable(const int param1, const unsigned int param2, const unsigned int param3, const int param4);

    void getVfb(const int param, int *sid);

    void updateVfb(const int param);

private:
    ComStack *m_comStack;
};

#endif