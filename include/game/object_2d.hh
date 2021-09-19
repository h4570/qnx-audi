/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_OBJECT_2D_
#define _QNX_AUDI_OBJECT_2D_

#include <GLES/egl.h>
#include "game/render_package.hh"

class Object2D
{

public:
    Object2D();
    ~Object2D();

    void setRenderPackage();

protected:
    RenderPackage m_renderPackage;
    GLfloat m_scale, m_x, m_y, m_width, m_height;
};

#endif