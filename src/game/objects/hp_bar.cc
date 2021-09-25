/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/objects/hp_bar.hh"

// ----
// Constructors/Destructors
// ----

HpBar::HpBar(const Screen &screen)
    : m_100("100hp"),
      m_90("90hp"),
      m_80("80hp"),
      m_70("70hp"),
      m_60("60hp"),
      m_50("50hp"),
      m_40("40hp"),
      m_30("30hp"),
      m_20("20hp"),
      m_10("10hp"),
      m_0("0hp")
{
#ifdef TARGET_AUDI
    m_y = 30.0F;
    m_x = 10.0F;
    m_width = 256.0F;
    m_height = 64.0F;
    m_scale = 1.0F;
#else
    m_width = 256.0F;
    m_height = 64.0F;
    m_scale = .5F;
#endif
}

HpBar::~HpBar()
{
}

// ----
// Methods
// ----

void HpBar::update(_Int16t playerHp)
{
    setRenderPackage();
    if (playerHp == 100)
        m_100.render(m_renderPackage);
    else if (playerHp >= 90)
        m_90.render(m_renderPackage);
    else if (playerHp >= 80)
        m_80.render(m_renderPackage);
    else if (playerHp >= 70)
        m_70.render(m_renderPackage);
    else if (playerHp >= 60)
        m_60.render(m_renderPackage);
    else if (playerHp >= 50)
        m_50.render(m_renderPackage);
    else if (playerHp >= 40)
        m_40.render(m_renderPackage);
    else if (playerHp >= 30)
        m_30.render(m_renderPackage);
    else if (playerHp >= 20)
        m_20.render(m_renderPackage);
    else if (playerHp >= 10)
        m_10.render(m_renderPackage);
    else
        m_0.render(m_renderPackage);
}