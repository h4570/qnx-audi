/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_PLAYER_
#define _QNX_AUDI_PLAYER_

#include "modules/keyboard/keyboard.hh"
#include "models/texture.hh"
#include "game/animation.hh"
#include "game/object_2d.hh"
#include "utils/debug.hh"

class Player : Object2D
{

public:
    Player(Keyboard *keyboard);
    ~Player();

    void update();

private:
    _Uint8t m_animCounter;
    Keyboard *m_keyboard;

    Animation
        m_attack1Animation,
        m_attack2Animation,
        m_attack3Animation,
        m_deathAnimation,
        m_idleAnimation;
};

#endif