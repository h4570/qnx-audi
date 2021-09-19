/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_LIGHT_BANDIT_
#define _QNX_AUDI_LIGHT_BANDIT_

#include "modules/keyboard/keyboard.hh"
#include "models/texture.hh"
#include "game/animation.hh"
#include "game/object_2d.hh"
#include "utils/debug.hh"

class LightBandit : Object2D
{

public:
    LightBandit(Keyboard *keyboard);
    ~LightBandit();

    void update();

private:
    _Uint8t m_animCounter;
    Animation
        m_idleAnimation,
        m_attackAnimation,
        m_deathAnimation,
        m_runAnimation;
};

#endif