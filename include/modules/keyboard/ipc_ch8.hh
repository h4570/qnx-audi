/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_IPC_CH8_
#define _QNX_AUDI_IPC_CH8_

#include "modules/keyboard/keyboard.hh"

#include <pthread.h>
#include <sys/select.h>

/** 
 * Class responsible for communication with Audi's keyboard.
 * Contains reversed functions from Audi's libraries.
 */
class IpcCh8 : public Keyboard
{

public:
    IpcCh8();
    ~IpcCh8();

    void init();
    void dispose();

    void ___thread();

private:
    static const int m_bufferSize = 0x100;

    pthread_t m_threadId;
    bool m_isConnected, m_shouldRun;
    int m_handle;
    char *m_buffer;
    fd_set m_readFds;
    struct timeval m_timeout;

    inline void reset()
    {
        m_isLeftPressed = false;
        m_isRightPressed = false;
        m_isExitPressed = false;
        m_isRetryPressed = false;
    };

    void connect();
    void disconnect();
};

#endif