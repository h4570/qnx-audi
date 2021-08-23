/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "modules/screen.hh"
#include "utils/debug.hh"

// ----
// Constructors/Destructors
// ----

Screen::Screen()
{
}

Screen::~Screen()
{
}

// ----
// Methods
// ----

void Screen::init()
{
    attachDevice();
}

void Screen::uninit()
{
    detachDevice();
}

void Screen::attachDevice()
{
    int res = gf_dev_attach(&m_gfDev, GF_DEVICE_INDEX(0), &m_gfInfo);
    if (res == GF_ERR_OK)
    {
        log("Screen: Device attached");
        return;
    }
    switch (res)
    {
    case GF_ERR_MEM:
        assert(false, "Failure to allocate memory for data structures");
        break;
    case GF_ERR_IODISPLAY:
        assert(false, "Could not access the /dev/io-display directory. Check to ensure that io-display is running");
        break;
    case GF_ERR_DEVICE:
        assert(false, "Could not find the requested device. Check the /dev/io-display directory to ensure the requested device is mounted");
        break;
    case GF_ERR_SHMEM:
        assert(false, "Could not open or map in the required shared memory");
        break;
    case GF_ERR_DLL:
        assert(false, "Error accessing the driver DLL or entrypoint");
        break;
    case GF_ERR_THREAD:
        assert(false, "Error registering thread");
        break;
    }
}

void Screen::detachDevice()
{
    assert(m_gfDev != NULL, "Screen: Device not attached");
    gf_dev_detach(m_gfDev);
    log("Screen: Device detached");
}