/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_TEXTURE_
#define _QNX_AUDI_TEXTURE_

#include <GLES/gl.h>
#include <xstring>

enum TextureType
{
    TEX_TYPE_RGB,
    TEX_TYPE_RGBA
};

/** Class which contains texture data. */
class Texture
{

public:
    Texture(const char *t_fullPath, const char *t_name, const TextureType t_type);
    ~Texture();

    // ----
    // Getters
    // ----

    /** Auto generated unique Id. */
    inline const uint32_t getId() const { return m_id; };

    inline const int getWidth() const { return m_width; };

    inline const int getHeight() const { return m_height; };

    inline const TextureType getType() const { return m_type; };

    const int getStbiType() const;

    inline const GLint getGlType() const { return m_type == TEX_TYPE_RGB ? GL_RGB : GL_RGBA; };

    /** 
     * Returns always width * width * (3 OR 4). 
     * 3 for RGB, 4 for RGBA.
     */
    inline const uint32_t getDataSize() const { return m_type == TEX_TYPE_RGB ? m_width * m_height * 3 : m_width * m_height * 4; };

    inline const unsigned char *getData() const { return m_data; };

    inline const std::string getName() const { return m_name; };

private:
    std::string m_name;
    TextureType m_type;
    uint32_t m_id;
    int m_width, m_height;
    unsigned char *m_data;
};

#endif