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
    : m_attackAnimation("ninja/attack", 9)
{
    m_width = 128.0F;
    m_height = 128.0F;
    m_x = 0;
    m_y = 0;
}

Player::~Player()
{
}

// ----
// Methods
// ----

void Player::update()
{
    GLfloat minX = m_x;
    GLfloat minY = m_y;
    GLfloat maxX = m_x + m_width;
    GLfloat maxY = m_y + m_height;

    m_attackAnimation.render(minX, minY, maxX, maxY);
}