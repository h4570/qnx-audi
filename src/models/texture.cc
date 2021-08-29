/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "models/texture.hh"
#include "utils/debug.hh"
#include <stdlib.h>
#include <string.h>

// ----
// Constructors/Destructors
// ----

Texture::Texture()
{
    m_id = rand() % 1000000;
    m_isMemoryAllocated = false;
    m_isNameSet = false;
    m_type = TEX_TYPE_RGB;
    m_width = 0;
    m_height = 0;
    m_data = NULL;
}

Texture::~Texture()
{
    m_name.erase();
    if (m_isMemoryAllocated)
        delete[] m_data;
}

// ----
// Methods
// ----

void Texture::allocateMemory(const uint16_t &t_width, const uint16_t &t_height, const TextureType &t_type)
{
    assert(!m_isMemoryAllocated, "Memory already allocated");
    assert(t_width <= 256 && t_height <= 256, "Given texture is too big");
    m_width = t_width;
    m_height = t_height;
    m_type = t_type;
    m_data = new unsigned char[getDataSize()];
    assert(m_data != NULL, "Allocate memory failed");
    m_isMemoryAllocated = true;
}

void Texture::setName(const char *t_val)
{
    assert(!m_isNameSet, "Can't set name, because was already set!");
    m_name = t_val;
    m_isNameSet = true;
}

void Texture::setData(const uint32_t &t_index, const unsigned char &t_val)
{
    assert(m_data != NULL, "Can't set data, because memory was not allocated");
    m_data[t_index] = t_val;
}
