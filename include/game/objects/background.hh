/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_BACKGROUND_
#define _QNX_AUDI_BACKGROUND_

#include "modules/keyboard/keyboard.hh"
#include "models/texture.hh"
#include "modules/screen.hh"
#include "game/static_image.hh"
#include "game/object_2d.hh"
#include "utils/debug.hh"

class Background : Object2D
{

public:
    Background(const Screen &screen);
    ~Background();

    void update();

private:
    StaticImage m_image;
};

#endif