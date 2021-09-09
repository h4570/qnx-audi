
#include "external/lmgr.h"
#include "utils/debug.hh"

#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void lmgrCheckVersion()
    {
        const int command = -0x3ff3fafa;
        const int dwords = 3;
        int data[dwords] = {0};

        comStackSend(command, &data, dwords * 4);
        assert(data[0] == 1 && data[1] == 1, "lmgrCheckVersion failed. Required version: 1.1");
        logMessage("[Audi] - lmgrCheckVersion: 1.1!");
    }

    void lmgrRegisterDisplayable(int param1, unsigned int param2, unsigned int param3, int param4)
    {
        const int command = -0x3febfb00;
        const int dwords = 5;
        int data[dwords] = {param1, param2, param3, param4, 0};

        comStackSend(command, data, dwords * 4);

        assert(data[4] != 0, "lmgrRegisterDisplayable failed.");
        logMessage("[Audi] - lmgrRegisterDisplayable: Success!");
    }

    void lmgrGetVfb(int param, int *sid)
    {
        assert(sid != NULL, "lmgrGetVfb failed: Wrong input parameter!");
        const int command = -0x3feffafd;
        const int dwords = 4;
        int data[dwords] = {param, -1, -1, -1};

        comStackSend(command, data, dwords * 4);
        sid[0] = data[1];
        sid[1] = data[2];
        sid[2] = data[3];
        logMessage("[Audi] - lmgrGetVfb: Success!");
    }

    void lmgrUpdateVfb(int param)
    {
        const int command = -0x7ffbfafc;
        const int dwords = 1;
        int data[dwords] = {param};

        comStackSend(command, data, dwords * 4);
        logMessage("[Audi] - lmgrGetVfb: Success!");
    }

#ifdef __cplusplus
}
#endif