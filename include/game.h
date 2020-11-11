#pragma once

#include "entity_manager.h"
#include "hud.h"

class Game
{
	public:
		Game(int screenWidth, int screenHeight);
		~Game();
		void gameLoop();

	private:
		int m_score = 0;
		bool m_isPaused = false;
		bool m_isDebugging = false;

		HUD m_hud;
		EntityManager m_entity_manager;

		void update();
		void draw();
};