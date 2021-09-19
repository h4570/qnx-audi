/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/animation.hh"
#include "utils/string.hh"
#include "config.hh"
#include <string>

// ----
// Constructors/Destructors
// ----

const GLfloat Animation::TEXTURE_COORDINATES[] = {
    0, 1,
    0, 0,
    1, 0,
    1, 1};

const GLubyte Animation::TEXTURE_INDICES[] = {0, 1, 2, 0, 2, 3};

Animation::Animation(const char *t_name, _Uint8t t_framesCount)
{
    m_name = t_name;
    logKeyValue("Constructing animation with name", m_name.c_str());
    m_framesCount = t_framesCount;
    m_path = ASSETS_PATH;
    m_path += '/';
    m_path += t_name;
    m_path += '/';

    GLuint *textureIds = new GLuint[t_framesCount];
    GL_CHECK(glGenTextures(t_framesCount, textureIds));
    m_textures = new Texture *[t_framesCount];
    m_textureIds = new GLuint[t_framesCount];

    GL_CHECK(glEnable(GL_TEXTURE_2D));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    for (_Uint8t i = 0; i < m_framesCount; i++)
    {
        char *iAsChar = intToChar((int)i);
        std::string fileName = m_path;
        fileName.append(iAsChar);
        fileName.append(".png");
        std::string name = t_name;
        name.append(iAsChar);
        delete[] iAsChar;

        m_textures[i] = new Texture(fileName.c_str(), name.c_str(), TEX_TYPE_RGBA);
        m_textureIds[i] = textureIds[i];

        GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureIds[i]));
        GL_CHECK(glColor4f(1.0F, 1.0F, 1.0F, 1.0F));
        GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, m_textures[i]->getGlType(),
                              m_textures[i]->getWidth(), m_textures[i]->getHeight(),
                              0, m_textures[i]->getGlType(), GL_UNSIGNED_BYTE, m_textures[i]->getData()));
    }
}

Animation::~Animation()
{
    logKeyValue("Destructing animation with name", m_name.c_str());
    for (_Uint8t i = 0; i < m_framesCount; i++)
    {
        delete m_textures[i];
        glDeleteTextures(1, &m_textureIds[i]);
    }
    delete[] m_textureIds;
}

// ----
// Methods
// ----

void Animation::render(const RenderPackage &package, _Uint8t &animCounter)
{
    GLfloat vertices[] = {
        package.minX, package.maxY,
        package.minX, package.minY,
        package.maxX, package.minY,
        package.maxX, package.maxY};

    GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureIds[animCounter]));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
    GL_CHECK(glTexCoordPointer(2, GL_FLOAT, 0, TEXTURE_COORDINATES));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, TEXTURE_INDICES));

    if (++animCounter > m_framesCount - 1)
        animCounter = 0;
}