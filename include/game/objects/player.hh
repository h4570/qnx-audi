/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_PLAYER_
#define _QNX_AUDI_PLAYER_

#include "modules/keyboard/keyboard.hh"
#include "models/texture.hh"
#include "game/objects/object_animation.hh"
#include "utils/debug.hh"
#include <GLES/egl.h>

class Player
{

public:
    Player(Keyboard *keyboard);
    ~Player();

    void update();

private:
    GLfloat m_x, m_y, m_width, m_height;
    ObjectAnimation m_attackAnimation;
};

#endif