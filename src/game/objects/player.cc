/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/objects/player.hh"

// ----
// Constructors/Destructors
// ----

Player::Player(Keyboard *keyboard)
    : m_attack1Animation("hero_knight/attack_1", 6),
      m_attack2Animation("hero_knight/attack_2", 6),
      m_attack3Animation("hero_knight/attack_3", 8),
      m_deathAnimation("hero_knight/death", 10),
      m_idleAnimation("hero_knight/idle", 8)
{
    m_currentAnimation = &m_idleAnimation;
    m_keyboard = keyboard;
    m_maxHp = 100;
    m_hp = 100;
    m_isAttacking = false;
    m_attackDamage = 10;

    m_attack1Animation.setAnimationState(Once);
    m_attack2Animation.setAnimationState(Once);
    m_attack3Animation.setAnimationState(Once);
    m_deathAnimation.setAnimationState(Once);

#ifdef TARGET_AUDI
    m_y = 120.0F + 90.0F;
    m_scale = 2.0F;
#else
    m_scale = 1.0F;
    m_y = 60.0F;
#endif

    m_width = 128.0F;
    m_height = 128.0F;
    m_x = -30.0F;
    m_animCounter = 0;

#ifdef TARGET_AUDI
    m_y += 90.0F;
#endif
}

Player::~Player()
{
}

// ----
// Methods
// ----

void Player::update()
{
    if (!isAlive())
        changeAnimation(&m_deathAnimation);
    else
    {
        if (m_keyboard->isLeftPressed() && m_keyboard->isRightPressed())
        {
            m_attackDamage = 100;
            m_isAttacking = true;
            changeAnimation(&m_attack3Animation);
        }
        else if (m_keyboard->isLeftPressed())
        {
            m_attackDamage = 10;
            m_isAttacking = true;
            changeAnimation(&m_attack1Animation);
        }
        else if (m_keyboard->isRightPressed())
        {
            m_attackDamage = 10;
            m_isAttacking = true;
            changeAnimation(&m_attack2Animation);
        }
    }

    setRenderPackage();
    m_currentAnimation->render(m_renderPackage, m_animCounter);

    if (isAlive() && m_currentAnimation->isFinished(m_animCounter))
    {
        m_isAttacking = false;
        resetAnimation();
        m_currentAnimation = &m_idleAnimation;
    }
}
