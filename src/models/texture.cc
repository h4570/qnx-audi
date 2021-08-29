/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "models/texture.hh"
#include "utils/debug.hh"

#include <malloc.h>
#define STBI_ASSERT(x) Debug::_assert(x, "STBI Error", __FILE__, __LINE__)
#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

// ----
// Constructors/Destructors
// ----

Texture::Texture(const char *t_fullPath, const char *t_name, const TextureType t_type)
{
    m_id = rand() % 1000000;
    m_type = t_type;
    m_name = t_name;
    int comp;
    m_data = stbi_load(t_fullPath, &m_width, &m_height, &comp, getStbiType());
    assert(m_data != NULL, "Failed to load texture");
}

Texture::~Texture() {}

const int Texture::getStbiType() const
{
    return m_type == TEX_TYPE_RGB ? STBI_rgb : STBI_rgb_alpha;
}
