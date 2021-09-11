/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "modules/ipc_ch8.hh"
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
    m_buffer = new char[m_bufferSize];
    assert(m_buffer != NULL, "Out of memory!");
}

IpcCh8::~IpcCh8()
{
    if (m_buffer != NULL)
        delete[] m_buffer;
}

// ----
// Methods
// ----

void IpcCh8::connect()
{
    assert(!m_isConnected, "Already connected");
    m_handle = open("/dev/ipc/ch8", 0);
    assert(m_handle != -1, "Failed to open /dev/ipc/ch8");
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

KeyboardEvent IpcCh8::waitForKey()
{
    assert(m_isConnected, "Not connected");
    read(m_handle, m_buffer, m_bufferSize);
    if (m_buffer[6] == 0x0 && m_buffer[7] == 0x1)
        return Left;
    else if (m_buffer[6] == 0x1 && m_buffer[7] == 0x0)
        return Right;
    else
        return Undefined;
}
