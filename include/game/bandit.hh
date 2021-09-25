/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_BANDIT_
#define _QNX_AUDI_BANDIT_

#include "models/texture.hh"
#include "game/animation.hh"
#include "game/object_2d.hh"
#include "utils/debug.hh"

class Bandit : public Object2D
{

public:
    Bandit();
    virtual ~Bandit();

    virtual void update() = 0;
    virtual void printHp() = 0;

    inline _Uint8t getHp() { return m_hp; }
    inline void reduceHp(_Uint8t value)
    {
        m_hp -= value;
        if (m_hp < 0)
            m_hp = 0;
    }
    inline bool isAlive() { return m_hp > 0; }
    inline bool isNearPlayer() { return m_endX > m_x; }
    inline bool isAttacking() { return isNearPlayer(); }
    inline _Uint8t getDamage() { return m_attackDamage; }
    inline void setPlayerKilled() { m_playerKilled = true; }
    inline void reset()
    {
        m_playerKilled = false;
        m_x = m_startX;
        m_attackDamage = m_startAttackDamage;
        m_speed = m_startSpeed;
    }

protected:
    bool m_playerKilled, m_wasDeathAnimationSet;
    _Int16t m_hp;
    _Uint8t m_animCounter;
    _Uint16t m_maxHp, m_attackDamage, m_startAttackDamage;

    Animation *m_currentAnimation;
    GLfloat m_speed, m_startSpeed, m_startX, m_endX;
};

#endif