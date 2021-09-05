/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "modules/audi.hh"
#include "utils/debug.hh"

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <devctl.h>

void __audi_hmi_destroy_func(void *value) {}

// ----
// Constructors/Destructors
// ----

Audi::Audi()
{
    m_isHmiKeyCreated = false;
}

Audi::~Audi()
{
}

// ----
// Methods
// ----

int Audi::hmiConnect()
{
    const int devDataPtrBytes = 12;

    int keyCreateResult = 0;
    int extraoutVar_WTF; // 3 bytes
    int data[3];

    memset(&data, 0, devDataPtrBytes);
    pthread_mutex_lock(&m_hmiMutex);
    if (!m_isHmiKeyCreated)
    {
        keyCreateResult = pthread_key_create(&m_hmiThreadKey, __audi_hmi_destroy_func);
        if (keyCreateResult != 0)
            return 1;
        m_isHmiKeyCreated = true;
    }
    pthread_mutex_unlock(&m_hmiMutex);
    int *threadKeyValue = (int *)pthread_getspecific(m_hmiThreadKey);
    if ((threadKeyValue == NULL) || (*threadKeyValue == -1))
    {
        threadKeyValue = (int *)(4);
        if (threadKeyValue == NULL)
            return 6;
        keyCreateResult = connectTo("/dev/layermanager");
        *threadKeyValue = keyCreateResult;
        pthread_setspecific(m_hmiThreadKey, threadKeyValue);
    }
    keyCreateResult = 1;
    if (*threadKeyValue != -1)
    {
        unsigned char timerResult = hmiConnectTimer(*threadKeyValue, 0xc00c0506, data, devDataPtrBytes);
        keyCreateResult = 3;
        if (concat3BytesWith1Byte(extraoutVar_WTF, timerResult) != 0)
        {
            if (data[0] != 1)
                keyCreateResult = 5;
            else
            {
                keyCreateResult = 0;
                if (data[1] != 1)
                    keyCreateResult = 5;
            }
        }
    }
    if (keyCreateResult != 0)
    {
        printf("HMI connect error code: %d\n", keyCreateResult);
        assert(false, "Error during HMI connection");
    }
    else
        logMessage("Connected to HMI");
    return keyCreateResult;
}

unsigned int Audi::hmiConnectTimer(int threadKeyValue, int dcmd, int *devDataPtr, int nBytes)
{
    bool bVar5;
    _Uint64t oldDifference, uVar3, old1, old2, nTime;
    int iVar2, iVar4, local_34, local_2c, local_24;

    iVar4 = 0;
    ClockTime(2, 0, &old1);
    old2 = old1;
    local_24 = local_34;
    do
    {
        oldDifference = old2 - old1;
        uVar3 = (local_24 - local_34) - (_Uint64t)(old2 < oldDifference);
        bVar5 = 4 < uVar3;
        if (uVar3 == 4)
        {
            bVar5 = 0xa817c7ff < oldDifference;
        }
        if (bVar5)
        {
            iVar4 = 0x104;
        }
        else
        {
            nTime = 0xa817c800 - oldDifference;
            local_2c = (4 - uVar3) - (unsigned int)(0xa817c800 < nTime);
            iVar2 = TimerTimeout(2, 0x50, 0, &nTime, 0);
            if (-1 < iVar2)
            {
                iVar4 = devctl(threadKeyValue, dcmd, devDataPtr, nBytes, 0);
            }
        }
        ClockTime(2, 0, &old2);
    } while (iVar4 == 4);
    return iVar4 == 0;
}

int Audi::connectTo(char *device)
{
    int *error;
    int result;

    result = -1;
    if (device != (char *)0x0)
    {
        do
        {
            result = open(device, 0x2002);
            if (-1 < result)
            {
                return result;
            }
            error = __get_errno_ptr();
        } while (*error == 4);
    }
    return result;
}
