/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_GAME_
#define _QNX_AUDI_GAME_

#include "modules/keyboard/keyboard.hh"
#include "modules/screen.hh"
#include "models/texture.hh"
#include "utils/debug.hh"

#include "game/objects/background.hh"
#include "game/objects/smart_background.hh"
#include "game/objects/heavy_bandit.hh"
#include "game/objects/light_bandit.hh"
#include "game/objects/player.hh"
#include "game/objects/hp_bar.hh"
#include "game/bandit.hh"

class Game
{

public:
    Game(Screen &screen, Keyboard *keyboard);
    ~Game();

    void init();
    void render();
    void uninit();

    inline void clear() { GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); }

private:
    inline bool isBanditAttackTourTime() { return m_difficultyTimer > m_difficulty; }
    void handleBanditAttack(Bandit &bandit);
    void handleBanditDefense(Bandit &bandit);
    void logic();

    unsigned int m_difficulty, m_difficultyTimer, m_score;
    _Uint8t m_initializer;
    Screen m_screen;
    Keyboard *m_keyboard;

    HpBar m_hpBar;
    // SmartBackground m_smartBackground;
    Background m_background;
    HeavyBandit m_heavyBandit;
    LightBandit m_lightBandit;
    Player m_player;

    static const int RESOLUTION;
};

#endif