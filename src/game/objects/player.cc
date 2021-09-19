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

    m_keyboard = keyboard;

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
    setRenderPackage();
    // TODO
    if (m_keyboard->isLeftPressed())
        m_attack2Animation.render(m_renderPackage, m_animCounter);
    else if (m_keyboard->isRightPressed())
        m_attack1Animation.render(m_renderPackage, m_animCounter);
    else
        m_idleAnimation.render(m_renderPackage, m_animCounter);
}