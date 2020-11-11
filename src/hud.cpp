#include "hud.h"

#include <string>

HUD::HUD()
{
	m_bgTexture = LoadTexture("assets/minestorm_background.png");
	m_fgTexture = LoadTexture("assets/minestorm_forground.png");
}

HUD::~HUD()
{
	UnloadTexture(m_bgTexture);
	UnloadTexture(m_fgTexture);
}

void HUD::drawBackground()
{
	DrawTexture(m_bgTexture, 0, 0, WHITE);
}

void HUD::draw(int score)
{
	Image screenData = GetScreenData();

	// Draw foreground
	DrawTexture(m_fgTexture, 0, 0, WHITE);

	float fontSize = 30.f;

	// Display Score
	{
		std::string scoreString = "Score: " + std::to_string(score);
		const char* scoreChar = scoreString.c_str();
		DrawText(scoreChar, (screenData.width - MeasureText(scoreChar, fontSize)) * 0.5f, 715, fontSize, WHITE);
	}

	fontSize = 10.f;

	// Display global keybinds
	{
		std::string keybindString = "Press 'SPACE'\nor 'P'to pause";
		const char* keybindChar = keybindString.c_str();
		DrawText(keybindChar, (screenData.width - MeasureText(keybindChar, fontSize)) * 0.875f, 715, fontSize, WHITE);
	}

	fontSize = 15.f;

	// Player 1
	{
		// Display keybinds
		{
			std::string keybindString = "Rotate: 'D' and 'G'\n";
			keybindString += "Move: 'R'\n";
			keybindString += "Shoot: 'F'\n";
			keybindString += "Teleport: 'E' or 'T'\n";
			const char* keybindChar = keybindString.c_str();
			DrawText(keybindChar, (screenData.width - MeasureText(keybindChar, fontSize)) * 0.2f, screenData.height / 6.f, fontSize, WHITE);
		}
	}

	// Player 2
	{
		// Display keybinds
		{
			std::string keybindString = "Rotate: 'J' and 'L'\n";
			keybindString += "Move: 'I'\n";
			keybindString += "Shoot: 'K'\n";
			keybindString += "Teleport: 'U' or 'O'\n";
			const char* keybindChar = keybindString.c_str();
			DrawText(keybindChar, (screenData.width - MeasureText(keybindChar, fontSize)) * 0.8f, screenData.height / 6.f, fontSize, WHITE);
		}
	}
}