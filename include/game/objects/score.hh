/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_SCORE_
#define _QNX_AUDI_SCORE_

#include "models/texture.hh"
#include "modules/screen.hh"
#include "game/static_image.hh"
#include "game/object_2d.hh"
#include "utils/debug.hh"

class Score : Object2D
{

public:
    Score(const Screen &screen);
    ~Score();

    void show();
    inline void increase() { m_score++; }
    inline void decrease() { m_score--; }
    inline void reset() { m_score = 0; }

private:
    unsigned int m_score;
    GLfloat m_startX;

    StaticImage *getStaticImageByNumber(_Int16t number);
    StaticImage m_9;
    StaticImage m_8;
    StaticImage m_7;
    StaticImage m_6;
    StaticImage m_5;
    StaticImage m_4;
    StaticImage m_3;
    StaticImage m_2;
    StaticImage m_1;
    StaticImage m_0;
};

#endif