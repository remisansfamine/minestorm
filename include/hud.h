#pragma once

#include <vector>

#include <raylib.h>

class Player;

class HUD
{
	public:
		HUD();
		~HUD();

		void drawHUD(int score);
		void drawMenu();
		void drawBackground();
		void drawForeground();
		void drawGameOver(int score);
	
		std::vector<Player>* m_player = nullptr;

	private:
		int m_screenWidth = 0;
		int m_screenHeight = 0;
		Texture2D m_bgTexture;
		Texture2D m_fgTexture;
};