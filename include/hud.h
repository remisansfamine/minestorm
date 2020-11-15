#pragma once

#include <raylib.h>

class HUD
{
	public:
		HUD();
		~HUD();
		void draw(int score);
		void drawBackground();

	private:
		Texture2D m_bgTexture;
		Texture2D m_fgTexture;
};