#pragma once

#include "entity_manager.h"
#include "hud.h"

enum class GameState
{
	MENU,
	INGAME,
	GAMEOVER
};

class Game
{
	public:
		Game(int screenWidth, int screenHeight);
		~Game();
		void gameLoop();

		static GameState m_gameState;

	private:
		int m_gameSpeed = 1;
		int m_score = 0;

		bool m_isPaused = false;
		bool m_isDebugging = false;

		HUD m_hud;
		EntityManager m_entityManager;

		void update();
		void draw();
};