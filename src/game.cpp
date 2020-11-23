#include "game.h"

#include "time.h"

GameState Game::m_gameState = GameState::MENU;

Game::Game(int screenWidth, int screenHeight)
{
    SetTargetFPS(60);

    srand(time(NULL));

    m_hud.m_player = &m_entityManager.m_players;
}

Game::~Game()
{
    CloseWindow();
}

void Game::gameLoop()
{
    // Setting the game loop and updating the game in function of its state

    while (!WindowShouldClose() && m_gameState != GameState::QUIT)
    {
        switch (m_gameState)
        {
            case GameState::MENU:
                updateMainMenu();
                break;

            case GameState::PAUSE:
                updatePauseMenu();
                break;

            case GameState::INGAME:
                updateGame();
                break;

            case GameState::GAMEOVER:
                if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_SPACE))
                    m_gameState = GameState::MENU;
                break;

            default:
                return;
        }

        draw();
    }
}

void Game::updateMainMenu()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        m_gameState = GameState::QUIT;
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        if (IsKeyPressed(m_entityManager.m_input[i].m_shoot))
        {
            m_entityManager.reset();
            m_entityManager.setPlayerCount(i + 1);
            m_gameState = GameState::INGAME;
        }
    }
}

void Game::updateGame()
{
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_P))
    {
        m_gameState = GameState::PAUSE;
        return;
    }

    if (IsKeyPressed(KEY_C))
        m_isDebugging = !m_isDebugging;

    float deltaTime = GetFrameTime();

    m_entityManager.update(deltaTime);
}

void Game::updatePauseMenu()
{
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_P))
        m_gameState = GameState::INGAME;

    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE))
        m_gameState = GameState::MENU;
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    m_hud.drawBackground();

    switch (m_gameState)
    {
        case GameState::MENU:
            m_hud.drawMainMenu();
            m_hud.drawForeground();
            break;

        case GameState::PAUSE:
            m_entityManager.draw(m_isDebugging);
            m_hud.drawForeground();
            m_hud.drawPauseMenu();
            m_hud.drawHUD();
            break;

        case GameState::INGAME:
            m_entityManager.draw(m_isDebugging);
            m_hud.drawForeground();
            m_hud.drawHUD();
            break;

        case GameState::GAMEOVER:
            m_hud.drawGameOver();
            m_hud.drawForeground();
            break;

        default:
            m_hud.drawForeground();
            m_hud.drawMainMenu();
    }

    EndDrawing();
}