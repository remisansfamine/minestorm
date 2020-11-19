#include "game.h"

#include "time.h"

GameState Game::m_gameState = GameState::MENU;

Game::Game(int screenWidth, int screenHeight)
{
    SetTargetFPS(60);

    srand(time(NULL));

    m_hud.m_player = &m_entityManager.m_player;
}

Game::~Game()
{
    CloseWindow();
}

void Game::gameLoop()
{
    while (!WindowShouldClose())
    {
        switch (m_gameState)
        {
            case GameState::MENU:
                if (IsKeyPressed(KEY_ESCAPE))
                    break;

                for (int i = 0; i < 4; i++)
                {
                    if (IsKeyPressed(m_entityManager.m_input[i].m_shoot))
                    {
                        m_entityManager.setPlayerCount(i + 1);
                        m_gameState = GameState::INGAME;
                    }
                }
                break;
            case GameState::INGAME:
                update();
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

void Game::update()
{
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_P))
        m_isPaused = !m_isPaused;

    if (IsKeyPressed(KEY_C))
        m_isDebugging = !m_isDebugging;

    if (m_isPaused)
        return;

    float deltaTime = GetFrameTime();

    m_entityManager.update(deltaTime);
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    m_hud.drawBackground();

    switch (m_gameState)
    {
        case GameState::MENU:
            m_hud.drawMenu();
            break;
        case GameState::INGAME:
            m_entityManager.draw(m_isDebugging);
            m_hud.drawHUD(m_score);
            break;
        case GameState::GAMEOVER:
            m_hud.drawGameOver(m_score);
            break;

        default:
            m_hud.drawMenu();
    }

    m_hud.drawForeground();

    EndDrawing();
}