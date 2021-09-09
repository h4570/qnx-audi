#include "external/com_stack.h"
#include "external/com_stackp.h"
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

#ifdef __cplusplus
extern "C"
{
#endif

    void comStackClearThreadKey(void *data)
    {
        if (!data)
            assert(false, "Data is null");
        free(data);
        pthread_setspecific(COM_STACK_KEY, NULL);
        logMessage("Cleared thread-key");
    }

    void comStackConnect()
    {
        logMessage("Connecting to the LayermanagerV2...");
        printf("comStackConnect: Thread (tid=%d), process (pid=%d)\n", pthread_self(), getpid());
        pthread_mutex_lock(&COM_STACK_MUTEX);
        if (COM_STACK_IS_KEY_CREATED == 0)
        {
            int status = pthread_key_create(&COM_STACK_KEY, &comStackClearThreadKey);
            if (status)
            {
                pthread_mutex_unlock(&COM_STACK_MUTEX);
                assert(false, "pthread_key_create() failed. The file descriptor couln\'t be set!");
            }
            else
                COM_STACK_IS_KEY_CREATED = 1;
        }
        pthread_mutex_unlock(&COM_STACK_MUTEX);
        void *threadDataValue = pthread_getspecific(COM_STACK_KEY);
        if (threadDataValue == NULL)
        {
            int *data = (int *)malloc(4);
            assert(data != NULL, "malloc() failed. The file descriptor couln\'t be set!");
            *data = comStackOpen("/dev/layermanager");
            assert(*data != -1, "comStackOpen() failed. The file descriptor couln\'t be set!");
            pthread_setspecific(COM_STACK_KEY, data);
        }
        logMessage("Connected successfully to the LayermanagerV2");
        printf("comStackConnect: Thread (tid=%d), process (pid=%d)\n", pthread_self(), getpid());
    }

    void comStackDisconnect()
    {
        logMessage("Disconnecting from the LayermanagerV2...");

        printf("comStackDisconnect: Thread (tid=%d), process (pid=%d)\n", pthread_self(), getpid());

        int *data = (int *)pthread_getspecific(COM_STACK_KEY);
        assert(data != NULL, "comStackDisconnect: Not connected yet or already disconnected!");

        int result = comStackClose(*data);
        assert(result == 1, "comStackDisconnect: comStackClose() failed!");
        free(data);
        pthread_setspecific(COM_STACK_KEY, NULL);

        logMessage("Disconnected successfully from the LayermanagerV2");
        printf("comStackDisconnect: Thread (tid=%d), process (pid=%d)\n", pthread_self(), getpid());
    }

    void comStackSend(int dcmd, void *data, size_t dataBytes)
    {
        _Uint64t start, nTime, last, diff = 0;
        const _Uint64t max = 0xa817c800 / 3;
        int callAmount = 0;

        int *threadKeyValue = (int *)pthread_getspecific(COM_STACK_KEY);
        if (threadKeyValue == NULL)
        {
            printf("comStackSend: Thread (tid=%d), process (pid=%d)\n", pthread_self(), getpid());
            assert(false, "Uninitialized file descriptor! Thread was either not connected or already disconnected!");
            return;
        }
        if (*threadKeyValue == -1)
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
                    errNumber = devctl(*threadKeyValue, dcmd, data, dataBytes, 0);
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

    int comStackOpen(const char *device)
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

    int comStackClose(const int fd)
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

#ifdef __cplusplus
}
#endif