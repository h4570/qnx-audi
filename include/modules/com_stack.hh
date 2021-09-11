/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_COM_STACK_
#define _QNX_AUDI_COM_STACK_

#include <pthread.h>

/** 
 * Class responsible for connection with Audi.
 * Contains reversed comStack* functions from Audi's libhybrid.so
 */
class ComStack
{

public:
    ComStack();
    ~ComStack();

    // ----
    // Getters
    // ----

    const bool &isKeyCreated() const { return m_isKeyCreated; };
    const bool isConnected() const { return m_isKeyCreated && pthread_getspecific(m_key) != NULL; };

    // ----
    //  Setters
    // ----

    // ----
    //  Other
    // ----

    void connect();

    void disconnect();

    void send(const int command, void *data, const size_t dataBytes);

private:
    pthread_key_t m_key;
    pthread_mutex_t m_mutex;
    bool m_isKeyCreated;

    void clearThreadKey(void *data);
    int openConnection(const char *device);
    int closeConnection(const int fd);
};

#endif