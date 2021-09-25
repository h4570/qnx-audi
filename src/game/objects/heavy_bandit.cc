/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/objects/heavy_bandit.hh"

// ----
// Constructors/Destructors
// ----

HeavyBandit::HeavyBandit()
    : m_idleAnimation("heavy_bandit/idle", 4),
      m_attackAnimation("heavy_bandit/attack", 8),
      m_deathAnimation("heavy_bandit/death", 1),
      m_runAnimation("heavy_bandit/run", 8)
{
    m_deathAnimation.setAnimationState(Once);
    m_currentAnimation = &m_runAnimation;

#ifdef TARGET_AUDI
    m_endX = 90.0F;
    m_startX = 750.0F;
#else
    m_endX = 50.0F;
    m_startX = 350.0F;
#endif

    m_startAttackDamage = 20;
    m_speed = m_startSpeed;
    m_attackDamage = m_startAttackDamage;
    m_x = m_startX;
}

HeavyBandit::~HeavyBandit()
{
}

// ----
// Methods
// ----

void HeavyBandit::update()
{
    if (m_x >= m_endX)
    {
        m_currentAnimation = &m_runAnimation;
        m_x -= m_speed;
    }
    else if (isNearPlayer())
    {
        if (!isAlive())
        {
            if (!m_wasDeathAnimationSet)
            {
                m_currentAnimation = &m_deathAnimation;
                m_animCounter = 0;
                m_wasDeathAnimationSet = true;
            }
            else if (m_deathAnimation.isFinished(m_animCounter))
            {
                m_wasDeathAnimationSet = false;
                m_hp = 100;
                m_speed += 0.1F;
                m_attackDamage += 2;
                m_x = m_startX;
            }
        }
        else if (m_playerKilled)
            m_currentAnimation = &m_idleAnimation;
        else
            m_currentAnimation = &m_attackAnimation;
    }

    setRenderPackage();
    m_currentAnimation->render(m_renderPackage, m_animCounter);
}