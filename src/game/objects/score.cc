/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/objects/score.hh"

// ----
// Constructors/Destructors
// ----

Score::Score(const Screen &screen)
    : m_9("n9"),
      m_8("n8"),
      m_7("n7"),
      m_6("n6"),
      m_5("n5"),
      m_4("n4"),
      m_3("n3"),
      m_2("n2"),
      m_1("n1"),
      m_0("n0")
{
    m_score = 0;
#ifdef TARGET_AUDI
    m_width = 64.0F;
    m_height = 64.0F;
    m_scale = .2F;
#else
    m_width = 64.0F;
    m_height = 64.0F;
    m_scale = .2F;
#endif
    m_startX = 290.0F;
    m_x = m_startX;
    m_y = 5.0F;
}

Score::~Score()
{
}

// ----
// Methods
// ----

void Score::show()
{
    StaticImage *image = NULL;
    _Int16t left = m_score % 10;
    _Int16t divided = m_score / 10;
    _Int16t right = divided % 10;

    m_x = m_startX;
    setRenderPackage();
    image = getStaticImageByNumber(right);
    if (image != &m_0)
        image->render(m_renderPackage);

    m_x = m_startX + (64.0F * m_scale);
    setRenderPackage();
    image = getStaticImageByNumber(left);
    image->render(m_renderPackage);
}

StaticImage *Score::getStaticImageByNumber(_Int16t number)
{
    if (number == 0)
        return &m_0;
    else if (number == 1)
        return &m_1;
    else if (number == 2)
        return &m_2;
    else if (number == 3)
        return &m_3;
    else if (number == 4)
        return &m_4;
    else if (number == 5)
        return &m_5;
    else if (number == 6)
        return &m_6;
    else if (number == 7)
        return &m_7;
    else if (number == 8)
        return &m_8;
    else if (number == 9)
        return &m_9;

    assert(false, "Number not found");
    return NULL;
}