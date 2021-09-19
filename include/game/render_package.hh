/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_RENDER_PACKAGE_
#define _QNX_AUDI_RENDER_PACKAGE_

#include <GLES/egl.h>

struct RenderPackage
{
    GLfloat minX;
    GLfloat minY;
    GLfloat maxX;
    GLfloat maxY;
};

#endif