/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_SCREEN_
#define _QNX_AUDI_SCREEN_

#include <gf/gf.h>

/** QNX screen */
class Screen
{

public:
    Screen();
    ~Screen();

    // ----
    // Getters
    // ----

    // ----
    //  Setters
    // ----

    // ----
    //  Other
    // ----

    /** Initialize QNX's device, display, layer, 3D rendering target, etc. */
    void init();

    /** Unitialize QNX rendering stuff */
    void uninit();

private:
    gf_dev_t m_gfDev;
    gf_dev_info_t m_gfInfo;

    void attachDevice();
    void detachDevice();
};

#endif