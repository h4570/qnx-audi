/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "modules/keyboard/ps2.hh"
#include "utils/debug.hh"

#include <hw/inout.h>
#include <sys/neutrino.h>
#include <unistd.h>

// ----
// Constructors/Destructors
// ----

Ps2::Ps2()
{
    m_isLeftPressed = false;
    m_isRightPressed = false;
    m_isExitPressed = false;
    m_shouldRun = true;
}

Ps2::~Ps2()
{
}

// ------ Hack
void *___ps2StaticThread(void *t_ptr)
{
    reinterpret_cast<Ps2 *>(t_ptr)->___thread();
    return NULL;
}
// ------

// ----
// Methods
// ----

void Ps2::init()
{
    pthread_create(&m_threadId, NULL, &___ps2StaticThread, this);
}

void Ps2::dispose()
{
    m_shouldRun = false;
    pthread_join(m_threadId, NULL);
}

void Ps2::___thread()
{
    const _Uint64t m_timeout = 1000;

    // request I/O privity
    ThreadCtl(_NTO_TCTL_IO, 0);

    // set up an event for the handler or the kernel to use to wake up
    // this thread. Use whatever type of event and event handling you want
    SIGEV_INTR_INIT(&m_event);

    // either register an event handler
    int id = InterruptAttachEvent(1, &m_event, _NTO_INTR_FLAGS_TRK_MSK);
    while (true)
    {
        // block here waiting for the event
        InterruptWait(0, &m_timeout);

        // if using a high frequency interrupt, don't print every interrupt
        InterruptUnmask(1, id);

        _Uint8t val = in8(0x60);

        if (val == 30)
            m_isLeftPressed = true;
        else if (val == 158)
            m_isLeftPressed = false;
        else if (val == 32)
            m_isRightPressed = true;
        else if (val == 160)
            m_isRightPressed = false;
        else if (val == 1)
            m_isExitPressed = true;
        else if (val == 129)
            m_isExitPressed = false;

        if (!m_shouldRun)
            break;

        delay(1);
    }
}
