/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/static_image.hh"
#include "utils/string.hh"
#include "config.hh"
#include <string>

// ----
// Constructors/Destructors
// ----

StaticImage::StaticImage(const char *t_name)
{
    m_name = t_name;
    logKeyValue("Constructing static image with name", m_name.c_str());
    m_path = ASSETS_PATH;
    m_path += "/static/";
    m_path += t_name;
    m_path += ".png";

    std::string fileName = m_path;
    std::string name = t_name;

    GL_CHECK(glGenTextures(1, &m_textureId));

    m_texture = new Texture(fileName.c_str(), name.c_str(), TEX_TYPE_RGBA);

    GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureId));
    GL_CHECK(glColor4f(1.0F, 1.0F, 1.0F, 1.0F));
    GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, m_texture->getGlType(),
                          m_texture->getWidth(), m_texture->getHeight(),
                          0, m_texture->getGlType(), GL_UNSIGNED_BYTE, m_texture->getData()));
}

StaticImage::~StaticImage()
{
    logKeyValue("Destructing static image with name", m_name.c_str());
    // glDeleteTextures(m_framesCount, m_textureIds); // What about this?
    delete m_texture;
}

// ----
// Methods
// ----

const GLfloat StaticImage::TEXTURE_COORDINATES[] = {
    0, 1, // 2
    0, 0, // 0
    1, 0, // 1
    1, 1  // 3
};

const GLubyte StaticImage::INDICES[] = {0, 1, 2, 3};

void StaticImage::render(const RenderPackage &package)
{
    /**
     *  0     1
     *  |\    |
     *  | \   |
     *  |  \  |
     *  |   \ |
     *  |__ _\|
     *  2     3
     */
    GLfloat vertices[] = {
        package.minX, package.maxY, // 2
        package.minX, package.minY, // 0
        package.maxX, package.minY, // 1
        package.maxX, package.maxY  // 3
    };

    GL_CHECK(glDisable(GL_BLEND));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureId));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
    GL_CHECK(glTexCoordPointer(2, GL_FLOAT, 0, TEXTURE_COORDINATES));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, INDICES));
}