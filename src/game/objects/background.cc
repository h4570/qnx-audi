/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/objects/background.hh"

// ----
// Constructors/Destructors
// ----

Background::Background(Keyboard *keyboard)
    : m_animation("background", 1)
{
    m_scale = 1.0F;
    m_width = 640.0F;
    m_height = 360.0F;
    m_animCounter = 0;
}

Background::~Background()
{
}

// ----
// Methods
// ----

void Background::update()
{
    setRenderPackage();
    m_animation.render(m_renderPackage, m_animCounter);
}