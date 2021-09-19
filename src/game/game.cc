/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/game.hh"

// ----
// Constructors/Destructors
// ----

Game::Game(Screen &screen, Keyboard *keyboard) : m_screen(screen),
                                                 m_lightBandit(keyboard),
                                                 m_player(keyboard)
{
    m_keyboard = keyboard;
}

Game::~Game() {}

// ----
// Methods
// ----

void Game::init()
{
    GL_CHECK(glMatrixMode(GL_PROJECTION));
    GL_CHECK(glLoadIdentity());
    GL_CHECK(glOrthof(0, (GLfloat)m_screen.getWidth(), (GLfloat)m_screen.getHeight(), 0, 0, 1));
    GL_CHECK(glMatrixMode(GL_MODELVIEW));
    GL_CHECK(glClearColor(.7F, .7F, .7F, 1.0F));
}

void Game::render()
{
    clear();

    m_lightBandit.update();
    m_player.update();
}

void Game::uninit()
{
}
