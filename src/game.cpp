#include "game.h"

Game::Game(int screenWidth, int screenHeight)
{
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    srand((unsigned int)GetFrameTime());

    m_hud.loadTextures();
}

Game::~Game()
{
    CloseWindow();
}

void Game::gameLoop()
{
    while (!WindowShouldClose())
    {
        update();

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

    m_entity_manager.update(deltaTime);
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    m_hud.drawBackground();
    m_entity_manager.draw(m_isDebugging);
    m_hud.draw(m_score);

    EndDrawing();
}