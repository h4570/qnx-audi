/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/objects/light_bandit.hh"

// ----
// Constructors/Destructors
// ----

LightBandit::LightBandit()
    : m_idleAnimation("light_bandit/idle", 4),
      m_attackAnimation("light_bandit/attack", 8),
      m_deathAnimation("light_bandit/death", 1),
      m_runAnimation("light_bandit/run", 8)
{
    m_deathAnimation.setAnimationState(Once);
    m_currentAnimation = &m_runAnimation;

#ifdef TARGET_AUDI
    m_endX = 80.0F;
    m_startX = 770.0F;
#else
    m_endX = 40.0F;
    m_startX = 370.0F;
#endif

    m_startAttackDamage = 10;
    m_startSpeed = 6.0F;
    m_speed = m_startSpeed;
    m_attackDamage = m_startAttackDamage;
    m_x = m_startX;
}

LightBandit::~LightBandit()
{
}

// ----
// Methods
// ----

void LightBandit::update()
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
                m_speed += 0.3F;
                m_attackDamage += 1;
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