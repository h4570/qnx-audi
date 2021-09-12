/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_PS2_
#define _QNX_AUDI_PS2_

#include "modules/keyboard/keyboard.hh"

#include <pthread.h>
#include <sys/siginfo.h>

/** Class responsible for communication with standard PS/2 keyboard. */
class Ps2 : public Keyboard
{

public:
    Ps2();
    ~Ps2();

    void init();
    void dispose();

    void ___thread();

private:
    struct sigevent m_event;

    pthread_t m_threadId;
    bool m_shouldRun;
};

#endif