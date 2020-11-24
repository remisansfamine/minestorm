#pragma once

#include "entity_manager.h"
#include "hud.h"
#include "particle_manager.h"

enum class GameState
{
	MENU,
	PAUSE,
	INGAME,
	GAMEOVER,
	QUIT
};

class Game
{
	private:
		int m_gameSpeed = 1;
		int m_score = 0;

		bool m_isDebugging = false;

		HUD				m_hud;
		EntityManager	m_entityManager;
		ParticleManager m_particleManager;

		void updateGame();
		void updateMainMenu();
		void updatePauseMenu();
		void draw();
		void drawPause();
		void drawGame();

	public:
		Game(int screenWidth, int screenHeight);
		~Game();

		void gameLoop();

		static GameState m_gameState;
};