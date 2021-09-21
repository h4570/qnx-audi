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
    _Uint8t m_initializer;
    Screen m_screen;
    Keyboard *m_keyboard;

    SmartBackground m_smartBackground;
    Background m_background;
    HeavyBandit m_heavyBandit;
    LightBandit m_lightBandit;
    Player m_player;
};

#endif