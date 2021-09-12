/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "modules/keyboard/ipc_ch8.hh"
#include "utils/debug.hh"

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// ----
// Constructors/Destructors
// ----

IpcCh8::IpcCh8()
{
    m_isConnected = false;
    m_isLeftPressed = false;
    m_isRightPressed = false;
    m_isExitPressed = false;
    m_shouldRun = true;
    m_buffer = new char[m_bufferSize];
    assert(m_buffer != NULL, "Out of memory!");
}

IpcCh8::~IpcCh8()
{
    if (m_buffer != NULL)
        delete[] m_buffer;
}

// ------ Hack
void *___ipcCh8StaticThread(void *t_ptr)
{
    reinterpret_cast<IpcCh8 *>(t_ptr)->___thread();
    return NULL;
}
// ------

// ----
// Methods
// ----

void IpcCh8::init()
{
    connect();
    pthread_create(&m_threadId, NULL, &___ipcCh8StaticThread, this);
}

void IpcCh8::dispose()
{
    m_shouldRun = false;
    pthread_join(m_threadId, NULL);
    disconnect();
}

void IpcCh8::___thread()
{
    assert(m_isConnected, "Not connected");
    while (true)
    {
        reset();
        if (select(m_handle + 1, &m_readFds, &m_writeFds, &m_exceptFds, &m_timeout) == 1)
        {
            read(m_handle, m_buffer, m_bufferSize);
            if (m_buffer[6] == 0x0 && m_buffer[7] == 0x1)
                m_isLeftPressed = true;
            else if (m_buffer[6] == 0x1 && m_buffer[7] == 0x0)
                m_isRightPressed = true;
            else // TODO: do it via else if
                m_isExitPressed = true;
        }

        if (!m_shouldRun)
            break;

        delay(1);
    }
}

void IpcCh8::connect()
{
    assert(!m_isConnected, "Already connected");
    m_handle = open("/dev/ipc/ch8", 0);
    assert(m_handle != -1, "Failed to open /dev/ipc/ch8");
    FD_ZERO(&m_readFds);
    FD_ZERO(&m_writeFds);
    FD_ZERO(&m_exceptFds);
    FD_SET(m_handle, &m_readFds);

    // m_timeout.tv_sec = 1;
    // m_timeout.tv_usec = 0;
    m_timeout.tv_sec = 0;
    m_timeout.tv_usec = 200000;
    m_isConnected = true;
    logMessage("Connected to /dev/ipc/ch8");
}

void IpcCh8::disconnect()
{
    assert(m_isConnected, "Not connected");
    close(m_handle);
    m_isConnected = false;
    logMessage("Disconnected from /dev/ipc/ch8");
}
