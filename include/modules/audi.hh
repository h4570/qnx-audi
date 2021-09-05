/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_MODULE_
#define _QNX_AUDI_MODULE_

#include <gf/gf.h>
#include <gf/gf3d.h>
#include <GLES/egl.h>

/** Reversed audi library functions */
class Audi
{

public:
    Audi();
    ~Audi();

    /** Connect to Audi HMI system */
    int hmiConnect();

private:
    bool m_isHmiKeyCreated;
    pthread_mutex_t m_hmiMutex;
    pthread_key_t m_hmiThreadKey;

    int connectTo(char *device);
    unsigned int hmiConnectTimer(int threadKeyValue, int dcmd, int *devDataPtr, int nBytes);
    inline int concat3BytesWith1Byte(int param1, unsigned char param2) { return (param1 << 8) | param2; }
};

#endif