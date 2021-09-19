/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/objects/heavy_bandit.hh"

// ----
// Constructors/Destructors
// ----

HeavyBandit::HeavyBandit(Keyboard *keyboard)
    : m_idleAnimation("heavy_bandit/idle", 4),
      m_attackAnimation("heavy_bandit/attack", 8),
      m_deathAnimation("heavy_bandit/death", 1),
      m_runAnimation("heavy_bandit/run", 8)
{

#ifdef TARGET_AUDI
    m_y = 176.0F + 90.0F;
    m_scale = 2.0F;
#else
    m_scale = 1.0F;
    m_y = 88.0F;
#endif

    m_width = 64.0F;
    m_height = 64.0F;
    m_x = m_width * m_scale;
    m_animCounter = 0;
}

HeavyBandit::~HeavyBandit()
{
}

// ----
// Methods
// ----

void HeavyBandit::update()
{
    setRenderPackage();
    m_attackAnimation.render(m_renderPackage, m_animCounter);
}