/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_NINJA_GIRL_
#define _QNX_AUDI_NINJA_GIRL_

#include "modules/keyboard/keyboard.hh"
#include "models/texture.hh"
#include "game/objects/object_animation.hh"
#include "utils/debug.hh"
#include <GLES/egl.h>

class NinjaGirl
{

public:
    NinjaGirl(Keyboard *keyboard);
    ~NinjaGirl();

    void update();

private:
    GLfloat m_x, m_y, m_width, m_height;
    ObjectAnimation m_idleAnimation;
};

#endif