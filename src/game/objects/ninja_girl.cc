/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/objects/ninja_girl.hh"

// ----
// Constructors/Destructors
// ----

NinjaGirl::NinjaGirl(Keyboard *keyboard)
    : m_idleAnimation("ninja/idle", 9)
{
    m_width = 128.0F;
    m_height = 128.0F;
    m_x = 128.0F;
    m_y = 0.0F;
}

NinjaGirl::~NinjaGirl()
{
}

// ----
// Methods
// ----

void NinjaGirl::update()
{
    GLfloat minX = m_x;
    GLfloat minY = m_y;
    GLfloat maxX = m_x + m_width;
    GLfloat maxY = m_y + m_height;

    m_idleAnimation.render(minX, minY, maxX, maxY);
}