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
    m_isRetryPressed = false;
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

#include "utils/string.hh"

void IpcCh8::___thread()
{
    assert(m_isConnected, "Not connected");
    while (true)
    {
        reset();
        // TODO: We cant make it non blocking via select()
        // logMessage("Check!");
        // if (select(m_handle + 1, &m_readFds, NULL, NULL, &m_timeout))
        // {
        //     logMessage("Read!");
        read(m_handle, m_buffer, m_bufferSize);

        // Snippet: If we want to check the data
        // for (int i = 0; i < m_bufferSize; i++)
        //     logKeyValue(intToChar(i), m_buffer[i]);

        _Int16t leftMovements = m_buffer[7];
        _Int16t rightMovements = m_buffer[6];
        _Int16t leftVolMovements = m_buffer[5];
        _Int16t rightVolMovements = m_buffer[4];

        if (leftMovements)
            m_isLeftPressed = true;
        else if (rightMovements)
            m_isRightPressed = true;
        else if (leftVolMovements)
            m_isRetryPressed = true;
        else if (rightVolMovements) // TODO: Hack for super attack.
        {
            m_isLeftPressed = true;
            m_isRightPressed = true;
        }
        else
            m_isExitPressed = true;
        // }

        if (!m_shouldRun)
            break;

        delay(200);
    }
}

void IpcCh8::connect()
{
    assert(!m_isConnected, "Already connected");
    m_handle = open("/dev/ipc/ch8", 0);
    assert(m_handle != -1, "Failed to open /dev/ipc/ch8");
    // FD_ZERO(&m_readFds);
    // FD_SET(m_handle, &m_readFds);

    // m_timeout.tv_sec = 1;
    // m_timeout.tv_usec = 0;
    // m_timeout.tv_sec = 0;
    // m_timeout.tv_usec = 200000;
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
