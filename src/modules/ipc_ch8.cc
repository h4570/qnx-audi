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
}

IpcCh8::~IpcCh8() {}

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

const int KEYBOARD_BUFFER_SIZE = 0x100; // Podejrzane maksymalne długości buforów,
const int SIZE = 48 * 4;
//char SETUP_DATA[SIZE] = {0};
char PREVIOUS_DATA[KEYBOARD_BUFFER_SIZE] = {0}; // tu zmienilem z SIZE na KEYBOARD_BUFFER_SIZE

int checkByte(char byte)
{
    if (byte < 6)
    {
        unsigned int check = 1 << (byte & 0x1f);
        if ((check & 0x13) != 0)
            return 0;
        if ((check & 0xc) != 0)
            return 2;
        if ((check & 0x20) != 0)
            return 1;
    }
    return 0xff;
}

unsigned int getKeyCode(char *keyboardBuffer)
{
    // logMessage("1");
    char data[SIZE] = {0};
    unsigned int result = 255;
    // memcpy(&data, &SETUP_DATA, SIZE);

    // logMessage("2");
    int counter1 = 0;
    do
    {
        logKeyValue("==counter1", counter1);
        unsigned int currentByte = (unsigned int)keyboardBuffer[counter1];
        unsigned int previousByte = (unsigned int)PREVIOUS_DATA[counter1];
        logKeyValue("==currentByte", currentByte);
        logKeyValue("==previousByte", previousByte);

        if (currentByte != previousByte)
        {
            // logMessage("3");

            int counter2 = 0;
            do
            {
                logKeyValue("====counter2", counter2);
                unsigned int uVar4;
                if (counter2 < 0) // nigdy?
                    uVar4 = 1 >> (~counter2 & 0x1f) + 1;
                else
                    uVar4 = 1 << (counter2 & 0x1f);
                // logMessage("4");
                bool left = (currentByte & uVar4 & 0xff) != 0;
                bool right = (previousByte & uVar4 & 0xff) != 0;
                // logKeyValue("left", left);
                // logKeyValue("right", right);
                if (left != right)
                {
                    // logMessage("5");
                    int fun2Res = checkByte(keyboardBuffer[17]);
                    // logKeyValue("fun2Res", fun2Res);
                    // logKeyValue("fun2Res, bool", fun2Res != 0xff);
                    if (fun2Res != 0xff)
                        result = (unsigned int)data[1 + (((fun2Res * 4 + counter1) * 8 + counter2) * 2)];
                }
                counter2 = counter2 + 1;
            } while (counter2 < 8);
        }
        counter1 = counter1 + 1;
    } while (counter1 < 4);
    // logMessage("5");
    memcpy(PREVIOUS_DATA, keyboardBuffer, KEYBOARD_BUFFER_SIZE);
    return result & 0xff;
}

#include <string>

void IpcCh8::getKey()
{
    int TEMP_SAFETY_BREAK = 0;
    assert(m_isConnected, "Not connected");
    unsigned int keyCode = 1;
    unsigned int keyCodeWeWant = 0;

    char keyboardBuffer[KEYBOARD_BUFFER_SIZE] = {0};

    do
    {
        // logMessage("c");
        read(m_handle, keyboardBuffer, KEYBOARD_BUFFER_SIZE);

        std::string chars = "";
        for (int i = 0; i < KEYBOARD_BUFFER_SIZE; i++)
        {
            chars.push_back(((char)keyboardBuffer[i]) + '0');
            chars += ", ";
        }

        // std::string ints = "";
        // for (int i = 0; i < KEYBOARD_BUFFER_SIZE; i = i + 4)
        // {
        //     ints.push_back(((int)keyboardBuffer[i]) + '0');
        //     ints += ", ";
        // }

        // logKeyValue("Chars", TEMP_SAFETY_BREAK);
        logMessage(chars.c_str());
        // logKeyValue("Ints", TEMP_SAFETY_BREAK);
        // logMessage(ints.c_str());

        // logMessage("d");
        // keyCode = getKeyCode(keyboardBuffer);
        // logKeyValue("keyCode", keyCode);
        // printf("e:%d\n", keyCode);
    } while (TEMP_SAFETY_BREAK++ < 6);
    // } while (keyCode != keyCodeWeWant);
    // printf("Keycode: %d\n", keyCode);
    logKeyValue("Keycode", keyCode);
    // logMessage("Keycode: success");
}