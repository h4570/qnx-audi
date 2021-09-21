/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_PLAYER_
#define _QNX_AUDI_PLAYER_

#include "modules/keyboard/keyboard.hh"
#include "models/texture.hh"
#include "game/animation.hh"
#include "game/object_2d.hh"
#include "utils/debug.hh"

class Player : Object2D
{

public:
    Player(Keyboard *keyboard);
    ~Player();

    void update();
    inline _Int16t getHp() { return m_hp; }
    inline void reduceHp(_Uint8t value)
    {
        m_hp -= value;
        if (m_hp < 0)
            m_hp = 0;
    }
    inline void addHp(_Uint8t value)
    {
        m_hp += value;
        if (m_hp > m_maxHp)
            m_hp = m_maxHp;
    }
    inline bool isAlive() { return m_hp > 0; }
    inline bool isAttacking() { return m_isAttacking; }
    inline _Uint8t getDamage() { return m_attackDamage; }
    inline void printHp() { logKeyValue("Player HP", m_hp); }

private:
    inline void resetAnimation() { m_animCounter = 0; }
    inline void changeAnimation(Animation *animation)
    {
        resetAnimation();
        m_currentAnimation = animation;
    }

    bool m_isAttacking;
    _Int16t m_hp;
    _Uint8t m_animCounter, m_maxHp, m_attackDamage;
    Keyboard *m_keyboard;

    Animation *m_currentAnimation;

    Animation
        m_attack1Animation,
        m_attack2Animation,
        m_attack3Animation,
        m_deathAnimation,
        m_idleAnimation;
};

#endif