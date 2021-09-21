/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_HP_BAR_
#define _QNX_AUDI_HP_BAR_

#include "models/texture.hh"
#include "modules/screen.hh"
#include "game/static_image.hh"
#include "game/object_2d.hh"
#include "utils/debug.hh"

class HpBar : Object2D
{

public:
    HpBar(const Screen &screen);
    ~HpBar();

    void update(_Int16t playerHp);

private:
    StaticImage m_100;
    StaticImage m_90;
    StaticImage m_80;
    StaticImage m_70;
    StaticImage m_60;
    StaticImage m_50;
    StaticImage m_40;
    StaticImage m_30;
    StaticImage m_20;
    StaticImage m_10;
    StaticImage m_0;
};

#endif