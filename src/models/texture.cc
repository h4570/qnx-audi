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
    id = rand() % 1000000;
    _isSizeSet = false;
    _isNameSet = false;
}

Texture::~Texture()
{
    name.erase();
    if (_isSizeSet)
        delete[] data;
}

// ----
// Methods
// ----

void Texture::setSize(const bool &t_width, const bool &t_height, const TextureType &t_type)
{
    assert(!_isSizeSet, "Can't set size, because was already set!");
    assert(t_width <= 256 && t_height <= 256, "Given texture is be too big.");
    width = t_width;
    height = t_height;
    _type = t_type;
    data = new unsigned char[getDataSize()];
    _isSizeSet = true;
}

void Texture::setName(const char *t_val)
{
    assert(!_isNameSet, "Can't set name, because was already set!");
    name = t_val;
    _isNameSet = true;
}
