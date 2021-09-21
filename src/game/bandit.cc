/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/bandit.hh"

// ----
// Constructors/Destructors
// ----

Bandit::Bandit()
{
    m_startX = 350.0F;
    m_endX = 50.0F;
    m_wasDeathAnimationSet = false;
    m_attackDamage = 10;
    m_playerKilled = false;
    m_maxHp = 100;
    m_hp = 100;
    m_speed = 3.0F;
    m_width = 64.0F;
    m_height = 64.0F;
    m_x = m_startX;
    m_animCounter = 0;

#ifdef TARGET_AUDI
    m_y = 176.0F + 90.0F;
    m_scale = 2.0F;
#else
    m_scale = 1.0F;
    m_y = 88.0F;
#endif
}

Bandit::~Bandit() {}
