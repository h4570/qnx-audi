/*
# Copyright 2021, qnx-audi - https://github.com/h4570/qnx-audi
# Licenced under Apache License 2.0
# Sandro Sobczyński <sandro.sobczynski@gmail.com>
*/

#include "game/game.hh"

// ----
// Constructors/Destructors
// ----

const int Game::RESOLUTION = 100;

Game::Game(Screen &screen, Keyboard *keyboard) : m_screen(screen),
                                                 m_hpBar(screen),
                                                 m_background(screen),
                                                 m_player(keyboard)
{
    m_keyboard = keyboard;
    m_initializer = 0;
    m_difficulty = 20 * Game::RESOLUTION;
    m_difficultyTimer = 0;
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
void Game::render()
{
    if (m_initializer < 2)
    {
        clear();
        m_initializer++;
    }

    logic();

    m_background.update();
    m_hpBar.update(m_player.getHp());
    // m_smartBackground.update(); // The idea was to move background to initializer area and update only smartBackground
    m_lightBandit.update();
    m_heavyBandit.update();
    m_player.update();
}

void Game::uninit()
{
}

void Game::logic()
{
    handleBanditDefense(m_lightBandit);
    handleBanditDefense(m_heavyBandit);

    if (!isBanditAttackTourTime())
    {
        m_difficultyTimer += 100;
        return;
    }
    m_difficultyTimer = 0;
    if (m_difficulty > 0)
        m_difficulty--;

    handleBanditAttack(m_lightBandit);
    handleBanditAttack(m_heavyBandit);

    m_player.printHp();
    m_heavyBandit.printHp();
    m_lightBandit.printHp();

    logMessage("Tour finished");
}

void Game::handleBanditAttack(Bandit &bandit)
{
    if (m_player.isAlive() && bandit.isNearPlayer() && bandit.isAttacking())
        m_player.reduceHp(bandit.getDamage());
    else if (!m_player.isAlive())
        bandit.setPlayerKilled();
}

void Game::handleBanditDefense(Bandit &bandit)
{
    if (bandit.isAlive() && bandit.isNearPlayer() && m_player.isAttacking())
    {
        bandit.reduceHp(m_player.getDamage());
        if (!bandit.isAlive())
            m_player.addHp(10);
    }
}