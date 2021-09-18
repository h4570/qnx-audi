/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#ifndef _QNX_AUDI_GAME_
#define _QNX_AUDI_GAME_

#include "modules/keyboard/keyboard.hh"
#include "game/objects/ninja_girl.hh"
#include "game/objects/player.hh"
#include "modules/screen.hh"
#include "models/texture.hh"
#include "utils/debug.hh"

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
    Screen m_screen;
    Keyboard *m_keyboard;

    NinjaGirl m_ninjaGirl;
    Player m_player;
};

#endif