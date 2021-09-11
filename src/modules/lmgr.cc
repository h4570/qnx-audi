/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "modules/lmgr.hh"
#include "utils/debug.hh"

// ----
// Constructors/Destructors
// ----

Lmgr::Lmgr(ComStack *comStack) : m_comStack(comStack) {}

Lmgr::~Lmgr() {}

// ----
// Methods
// ----

void Lmgr::checkVersion()
{
    const int command = -0x3ff3fafa;
    const int dwords = 3;
    int data[dwords] = {0};

    m_comStack->send(command, &data, dwords * 4);
    assert(data[0] == 1 && data[1] == 1, "lmgrCheckVersion failed. Required version: 1.1");
    logMessage("[Audi] - lmgrCheckVersion: 1.1!");
}

void Lmgr::registerDisplayable(const int param1, const unsigned int param2, const unsigned int param3, const int param4)
{
    const int command = -0x3febfb00;
    const int dwords = 5;
    int data[dwords] = {param1, param2, param3, param4, 0};

    m_comStack->send(command, data, dwords * 4);

    assert(data[4] != 0, "lmgrRegisterDisplayable failed.");
    logMessage("[Audi] - lmgrRegisterDisplayable: Success!");
}

void Lmgr::getVfb(const int param, int *sid)
{
    assert(sid != NULL, "lmgrGetVfb failed: Wrong input parameter!");
    const int command = -0x3feffafd;
    const int dwords = 4;
    int data[dwords] = {param, -1, -1, -1};

    m_comStack->send(command, data, dwords * 4);
    sid[0] = data[1];
    sid[1] = data[2];
    sid[2] = data[3];
    logMessage("[Audi] - lmgrGetVfb: Success!");
}

void Lmgr::updateVfb(const int param)
{
    const int command = -0x7ffbfafc;
    const int dwords = 1;
    int data[dwords] = {param};

    m_comStack->send(command, data, dwords * 4);
    logMessage("[Audi] - lmgrGetVfb: Success!");
}
