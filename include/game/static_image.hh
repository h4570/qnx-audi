/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_STATIC_IMAGE_
#define _QNX_AUDI_STATIC_IMAGE_

#include "models/texture.hh"
#include "utils/debug.hh"
#include "game/render_package.hh"
#include <GLES/egl.h>

class StaticImage
{
public:
    StaticImage(const char *t_name);
    ~StaticImage();

    void render(const RenderPackage &package);

private:
    std::string m_path, m_name;
    Texture *m_texture;
    GLuint m_textureId;

    static const GLfloat TEXTURE_COORDINATES[];
    static const GLubyte INDICES[];
};

#endif