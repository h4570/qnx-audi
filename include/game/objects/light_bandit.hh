/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_LIGHT_BANDIT_
#define _QNX_AUDI_LIGHT_BANDIT_

#include "game/bandit.hh"

class LightBandit : public Bandit
{

public:
    LightBandit();
    ~LightBandit();

    void update();
    inline void printHp() { logKeyValue("Light bandit HP", m_hp); }

private:
    Animation
        m_idleAnimation,
        m_attackAnimation,
        m_deathAnimation,
        m_runAnimation;
};

#endif