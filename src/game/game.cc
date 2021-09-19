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
                                                 m_smartBackground(screen),
                                                 m_background(screen),
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

    GL_CHECK(glEnable(GL_TEXTURE_2D));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GL_CHECK(glDisable(GL_BLEND));
    GL_CHECK(glDisable(GL_FOG));
    GL_CHECK(glDisable(GL_LIGHTING));
    GL_CHECK(glDisable(GL_CULL_FACE));
    GL_CHECK(glDisable(GL_ALPHA_TEST));
    GL_CHECK(glDisable(GL_COLOR_LOGIC_OP));
    GL_CHECK(glDisable(GL_DITHER));
    GL_CHECK(glDisable(GL_STENCIL_TEST));
    GL_CHECK(glDisable(GL_DEPTH_TEST));
    GL_CHECK(glDisable(GL_POINT_SMOOTH));
    GL_CHECK(glDisable(GL_LINE_SMOOTH));
    GL_CHECK(glDisable(GL_SCISSOR_TEST));
    GL_CHECK(glDisable(GL_COLOR_MATERIAL));
    GL_CHECK(glDisable(GL_NORMALIZE));
    GL_CHECK(glDisable(GL_RESCALE_NORMAL));
    GL_CHECK(glDisable(GL_POLYGON_OFFSET_FILL));
    GL_CHECK(glDisable(GL_MULTISAMPLE));
    GL_CHECK(glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE));
    GL_CHECK(glDisable(GL_SAMPLE_ALPHA_TO_ONE));
    GL_CHECK(glDisable(GL_SAMPLE_COVERAGE));

    GL_CHECK(glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST));
}
int test = 0;
void Game::render()
{
    if (test < 2)
    {
        clear();
        m_background.update();
        test++;
    }

    m_smartBackground.update();
    m_lightBandit.update();
    m_player.update();
}

void Game::uninit()
{
}
