/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_TEXTURE_
#define _QNX_AUDI_TEXTURE_

#include <stdint.h>
#include <xstring>

enum TextureType
{
    TEX_TYPE_RGB,
    TEX_TYPE_RGBA
};

/** 
 * Class which contains texture data.
 * Textures are paired with meshes/sprites via addLink() and 
 * removeLink() functions which use meshId/spriteId and materialId (for mesh).
 */
class Texture
{

public:
    Texture();
    ~Texture();

    // ----
    // Getters
    // ----

    /** 
     * Auto generated unique Id. 
     * Core role of this variable is to dont send 
     * again texture in renderer, when last sent texture id
     * by renderer will be equal to this id.
     */
    inline const uint32_t getId() const { return m_id; };

    inline const uint16_t getWidth() const { return m_width; };

    inline const uint16_t getHeight() const { return m_height; };

    inline const TextureType getType() const { return m_type; };

    /** 
     * Returns always width * width * 3/4. 
     * 3 for RGB, 4 for RGBA.
     */
    inline const uint32_t getDataSize() const { return m_type == TEX_TYPE_RGB ? m_width * m_height * 3 : m_width * m_height * 4; };

    /** 
     * Texture data, used by renderer.
     * Array of size getDataSize().
     */
    inline const unsigned char *getData() const { return m_data; };

    /** 
     * Get texture name.
     * For "textures/abc.bmp" result will be: "abc"
     */
    inline const std::string getName() const { return m_name; };

    // ----
    //  Setters
    // ----

    /** 
     * Set texture size and allocate texture data
     * Do not call this method unless you know what you do.
     * Should be called by data loader. 
     */
    void allocateMemory(const uint16_t &t_width, const uint16_t &t_height, const TextureType &t_type);

    /** 
     * Do not call this method unless you know what you do.
     * Should be called by data loader. 
     */
    void setHeight(const uint16_t &t_val) { m_height = t_val; }

    /** 
     * Do not call this method unless you know what you do.
     * Should be called by data loader. 
     */
    void setData(const uint32_t &t_index, const unsigned char &t_val);

    /** 
     * Set texture name. 
     * Should be the file name without extension
     */
    void setName(const char *t_val);

    // ----
    //  Other
    // ----

    inline const bool &isNameSet() const { return m_isNameSet; };

    inline const bool &isMemoryAllocated() const { return m_isMemoryAllocated; };

private:
    std::string m_name;
    TextureType m_type;
    uint32_t m_id;
    uint16_t m_width, m_height;
    bool m_isNameSet, m_isMemoryAllocated;
    unsigned char *m_data;
};

#endif