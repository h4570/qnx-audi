/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_LMGR_
#define _QNX_AUDI_LMGR_

#include "modules/com_stack.hh"
#include <gf/gf.h>

struct Vfb
{
    gf_sid_t sid;
    int val2;
    int val3;
};

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

    void registerDisplayable(const int param1, const int param2, const int param3, const int param4);

    void getVfb(const int param, Vfb *vfb);

    void updateVfb(const int param);

private:
    ComStack *m_comStack;
};

#endif