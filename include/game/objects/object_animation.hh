/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_OBJECT_ANIMATION_
#define _QNX_AUDI_OBJECT_ANIMATION_

#include "models/texture.hh"
#include "utils/debug.hh"
#include <GLES/egl.h>

class ObjectAnimation
{
public:
    ObjectAnimation(const char *t_name, _Uint8t t_framesCount);
    ~ObjectAnimation();

    void render(const GLfloat &minX, const GLfloat &minY, const GLfloat &maxX, const GLfloat &maxY);

private:
    _Uint8t m_animCounter, m_framesCount;
    std::string m_path, m_name;
    Texture **m_textures;
    GLuint *m_textureIds;

    static const GLfloat TEXTURE_COORDINATES[];
    static const GLubyte TEXTURE_INDICES[];
};

#endif