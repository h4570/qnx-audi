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

Animation::Animation(const char *t_name, _Uint8t t_framesCount)
{
    m_state = Repeat;
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
    // glDeleteTextures(m_framesCount, m_textureIds); // What about this?
    for (_Uint8t i = 0; i < m_framesCount; i++)
        delete m_textures[i];
    delete[] m_textureIds;
}

// ----
// Methods
// ----

const GLfloat Animation::TEXTURE_COORDINATES[] = {
    0, 1, // 2
    0, 0, // 0
    1, 0, // 1
    1, 1  // 3
};

const GLubyte Animation::INDICES[] = {0, 1, 2, 3};

void Animation::render(const RenderPackage &package, _Uint8t &animCounter)
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

    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureIds[animCounter]));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
    GL_CHECK(glTexCoordPointer(2, GL_FLOAT, 0, TEXTURE_COORDINATES));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, INDICES));

    if (animCounter <= m_framesCount - 1)
        animCounter++;
    if (animCounter > m_framesCount - 1)
        if (m_state == Repeat)
            animCounter = 0;
}