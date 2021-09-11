/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_IPC_CH8_
#define _QNX_AUDI_IPC_CH8_

/** 
 * Class responsible for communication with Audi's keyboard.
 * Contains reversed functions from Audi's libraries.
 */
class IpcCh8
{

public:
    IpcCh8();
    ~IpcCh8();

    // ----
    // Getters
    // ----

    const bool &isConnected() const { return m_isConnected; };

    // ----
    //  Other
    // ----

    void connect();

    void disconnect();

    void getKey();

private:
    bool m_isConnected;
    int m_handle;
};

#endif