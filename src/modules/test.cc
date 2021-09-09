/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "utils/debug.hh"

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <devctl.h>
#include <process.h>

int w_lmgrGetVfb(undefined4 param_1, undefined4 *param_2)

{
    int iVar1;
    undefined4 local_1c;
    undefined4 local_18;
    undefined4 local_14;
    undefined4 local_10;

    local_18 = 0xffffffff;
    local_14 = 0xffffffff;
    local_10 = 0xffffffff;
    local_1c = param_1;
    if (param_2 == (undefined4 *)0x0)
    {
        printf("lmgrGetVfb failed: Wrong input parameter!");
        iVar1 = 6;
    }
    else
    {
        iVar1 = comStackSend(0xc0100503, &local_1c, 0x10);
        if (iVar1 == 0)
        {
            *param_2 = local_18;
            param_2[1] = local_14;
            param_2[2] = local_10;
        }
        else
        {
            printf("lmgrGetVfb failed!");
        }
    }
    return iVar1;
}
