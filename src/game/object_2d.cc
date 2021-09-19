/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/object_2d.hh"

// ----
// Constructors/Destructors
// ----

Object2D::Object2D()
{
    m_scale = 1.0F;
    m_width = 0.0F;
    m_height = 0.0F;
    m_x = 0.0F;
    m_y = 0.0F;
}

Object2D::~Object2D() {}

// ----
// Methods
// ----

void Object2D::setRenderPackage()
{
    m_renderPackage.minX = m_x;
    m_renderPackage.minY = m_y;
    m_renderPackage.maxX = m_x + (m_width * m_scale);
    m_renderPackage.maxY = m_y + (m_height * m_scale);
}