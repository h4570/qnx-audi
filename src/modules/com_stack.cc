/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "modules/com_stack.hh"
#include "utils/debug.hh"

#include <sys/neutrino.h>
#include <devctl.h>
#include <process.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>

// ----
// Constructors/Destructors
// ----

ComStack::ComStack()
{
    m_isKeyCreated = false;
}

ComStack::~ComStack()
{
    if (isConnected())
        disconnect();
    if (isKeyCreated())
    {
        pthread_key_delete(m_key);
        m_isKeyCreated = false;
    }
}

// ------ Dirty hack
pthread_key_t *___latest_com_stack_key;
static void clearComStackThreadKey(void *data)
{
    if (!data)
        assert(false, "Data is null");
    free(data);
    pthread_setspecific(*___latest_com_stack_key, NULL);
    logMessage("Cleared thread-key");
}
// ------

// ----
// Methods
// ----

void ComStack::connect()
{
    assert(!isConnected(), "Already connected");
    logMessage("Connecting to the LayermanagerV2...");
    printf("comStackConnect: Thread (tid=%d), process (pid=%d)\n", pthread_self(), getpid());
    pthread_mutex_lock(&m_mutex);
    if (isKeyCreated() == 0)
    {
        ___latest_com_stack_key = &m_key;
        int status = pthread_key_create(&m_key, &clearComStackThreadKey);
        if (status)
        {
            pthread_mutex_unlock(&m_mutex);
            assert(false, "pthread_key_create() failed. The file descriptor couln\'t be set!");
        }
        else
            m_isKeyCreated = true;
    }
    pthread_mutex_unlock(&m_mutex);
    void *threadDataValue = pthread_getspecific(m_key);
    if (threadDataValue == NULL)
    {
        int *data = (int *)malloc(4);
        assert(data != NULL, "malloc() failed. The file descriptor couln\'t be set!");
        *data = openConnection("/dev/layermanager");
        assert(*data != -1, "comStackOpen() failed. The file descriptor couln\'t be set!");
        pthread_setspecific(m_key, data);
    }
    logMessage("Connected successfully to the LayermanagerV2");
    printf("comStackConnect: Thread (tid=%d), process (pid=%d)\n", pthread_self(), getpid());
}

void ComStack::disconnect()
{
    assert(isConnected(), "Not connected");
    logMessage("Disconnecting from the LayermanagerV2...");

    printf("comStackDisconnect: Thread (tid=%d), process (pid=%d)\n", pthread_self(), getpid());

    int *data = (int *)pthread_getspecific(m_key);
    assert(data != NULL, "comStackDisconnect: Not connected yet or already disconnected!");

    int result = closeConnection(*data);
    assert(result == 1, "comStackDisconnect: comStackClose() failed!");
    free(data);
    pthread_setspecific(m_key, NULL);

    logMessage("Disconnected successfully from the LayermanagerV2");
    printf("comStackDisconnect: Thread (tid=%d), process (pid=%d)\n", pthread_self(), getpid());
}

void ComStack::send(int command, void *data, size_t dataBytes)
{
    assert(isConnected(), "Not connected");
    _Uint64t start, nTime, last, diff = 0;
    const _Uint64t max = 0xa817c800 / 3;
    int callAmount = 0;

    int *threadKeyValue = (int *)pthread_getspecific(m_key);
    if (threadKeyValue == NULL)
    {
        printf("comStackSend: Thread (tid=%d), process (pid=%d)\n", pthread_self(), getpid());
        assert(false, "Uninitialized file descriptor! Thread was either not connected or already disconnected!");
        return;
    }
    else if (*threadKeyValue == -1)
    {
        printf("comStackSend: Thread (tid=%d), process (pid=%d)\n", pthread_self(), getpid());
        assert(false, "Invalid file descriptor!");
        return;
    }

    int errNumber = 0;
    ClockTime(CLOCK_MONOTONIC, 0, &start);
    last = start;
    do
    {
        diff = last - start;
        if (diff > max)
            errNumber = 0x104;
        else
        {
            nTime = max - diff;
            int timerResult = TimerTimeout(CLOCK_MONOTONIC, 0x50, 0, &nTime, 0);
            if (timerResult > -1)
            {
                errNumber = devctl(*threadKeyValue, command, data, dataBytes, 0);
                callAmount++;
            }
        }
        ClockTime(CLOCK_MONOTONIC, 0, &last);
    } while (errNumber == 4);
    if (errNumber)
    {
        printf("comStackSend: Thread (tid=%d), process (pid=%d), error = %d: %s\n", pthread_self(), getpid(), errNumber, strerror(errNumber));
        assert(false, "devctl() failed");
    }
    printf("comStackSend: Success. (devctl called %d times)\n", callAmount);
}

int ComStack::openConnection(const char *device)
{
    int status;
    int result = -1;
    if (device)
    {
        do
        {
            result = open(device, 0x2002);
            if (-1 < result)
                return result;
            status = *__get_errno_ptr();
        } while (status == 4);
    }
    if (status)
    {
        printf("comStackOpen: Thread (tid=%d), process (pid=%d), error %d: %s\n", pthread_self(), getpid(), status, strerror(status));
        assert(false, "open() failed!");
    }
    return result;
}

int ComStack::closeConnection(const int fd)
{
    int status;
    int result = -1;
    assert(fd, "comStackClose: Wrong file descriptor!");

    do
    {
        result = close(fd);
        if (-1 < result)
            return result;
        status = *__get_errno_ptr();
    } while (status == 4);
    if ((result == 0x59) || (result == 0))
        status = 1;
    if (status)
    {
        printf("comStackClose: Thread (tid=%d), process (pid=%d), error %d: %s\n", pthread_self(), getpid(), status, strerror(status));
        assert(false, "close() failed!");
    }
    return result;
}
