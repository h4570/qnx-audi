/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/objects/light_bandit.hh"

// ----
// Constructors/Destructors
// ----

LightBandit::LightBandit(Keyboard *keyboard)
    : m_idleAnimation("light_bandit/idle", 4),
      m_attackAnimation("light_bandit/attack", 8),
      m_deathAnimation("light_bandit/death", 1),
      m_runAnimation("light_bandit/run", 8)
{
    m_scale = 2.0F;
    m_width = 64.0F;
    m_height = 64.0F;
    m_x = m_width * m_scale;
    m_y = 176.0F;
    m_animCounter = 0;
}

LightBandit::~LightBandit()
{
}

// ----
// Methods
// ----

void LightBandit::update()
{
    setRenderPackage();
    m_idleAnimation.render(m_renderPackage, m_animCounter);
}