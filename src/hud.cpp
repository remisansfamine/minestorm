#include "hud.h"

#include <string>

#include "player.h"

HUD::HUD()
{
	m_bgTexture = LoadTexture("assets/minestorm_background.png");
	m_fgTexture = LoadTexture("assets/minestorm_forground.png");

	Image screenData = GetScreenData();

	m_screenWidth = screenData.width;
	m_screenHeight = screenData.height;
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

void DrawAlignedText(const char* text, float offset, int x, int y, float fontSize, Color color)
{
	DrawText(text, x - MeasureText(text, fontSize) * offset, y, fontSize, color);
}

void HUD::drawMenu()
{
	float fontSize = 30.f;

	DrawAlignedText("Do you want to play ?", 0.5f, m_screenWidth * 0.5f, m_screenHeight / 4.25f, fontSize, WHITE);

	fontSize = 17.5f;
	DrawAlignedText("Press 'F':                        Solo Mode", 0.5f, m_screenWidth * 0.5f, m_screenHeight / 3.5f, fontSize, LIME);
	DrawAlignedText("Press 'K':             Two players Mode", 0.5f, m_screenWidth * 0.5f, m_screenHeight / 3.25f, fontSize, BLUE);
	DrawAlignedText("Press 'DOWN':    Three players Mode", 0.5f, m_screenWidth * 0.5f, m_screenHeight / 3.f, fontSize, WHITE);
	DrawAlignedText("Press 'Keypad 5': Four players Mode", 0.5f, m_screenWidth * 0.5f, m_screenHeight / 2.75f, fontSize, PINK);
	DrawAlignedText("Press 'Esc':                   Exit", 0.5f, m_screenWidth * 0.5f, m_screenHeight / 2.5f, fontSize, RED);
}

void HUD::drawForeground()
{
	// Draw foreground
	DrawTexture(m_fgTexture, 0, 0, WHITE);
}

void HUD::drawGameOver(int score)
{
	float fontSize = 30.f;
	DrawAlignedText("GAME OVER", 0.5f, m_screenWidth * 0.5f, m_screenHeight / 3.75f, fontSize, WHITE);

	fontSize = 25.f;
	DrawAlignedText("Score: ", 0.5f, m_screenWidth * 0.5f, m_screenHeight / 3.25f, fontSize, GREEN);

	fontSize = 17.5f;
	DrawAlignedText("Press 'Esc' or 'SPACE:      Back to menu", 0.5f, m_screenWidth * 0.5f, m_screenHeight / 2.75f, fontSize, BLUE);

}

void HUD::drawHUD(int score)
{
	float fontSize = 30.f;

	// Display Score
	{
		std::string scoreString = "Score: " + std::to_string(score);
		const char* scoreChar = scoreString.c_str();
		DrawText(scoreChar, (m_screenWidth - MeasureText(scoreChar, fontSize)) * 0.5f, 715, fontSize, WHITE);
	}

	fontSize = 10.f;

	// Display global keybinds
	{
		std::string keybindString = "Press 'SPACE'\nor 'P' to pause";
		const char* keybindChar = keybindString.c_str();
		DrawText(keybindChar, (m_screenWidth - MeasureText(keybindChar, fontSize)) * 0.875f, 715, fontSize, WHITE);
	}

	fontSize = 15.f;

	if (!m_player || m_player->size() == 0)
		return;

	// Player 1
	{
		for (int i = 0; i < m_player->at(0).m_life; i++)
			DrawCircle(m_screenWidth * 0.2f + 5 * (i * 3 - 4), m_screenHeight * 0.125f, 5, m_player->at(0).m_color);

		// Display score
		{
			std::string infos = "Score: " + std::to_string(m_player->at(0).m_score);
			infos +=	"\nRotate: 'D' and 'G'\n"
						"Move: 'R'\n"
						"Shoot: 'F'\n"
						"Teleport: 'E' or 'T'\n";
			DrawAlignedText(infos.c_str(), 0.2f, m_screenWidth * 0.2f, m_screenHeight / 7.f, fontSize, WHITE);
		}
	}

	if (m_player->size() < 2)
		return;

	// Player 2
	{
		for (int i = 0; i < m_player->at(1).m_life; i++)
			DrawCircle((m_screenWidth * 0.8f + 5 * (i * 3 - 4)), m_screenHeight * 0.125f, 5, m_player->at(1).m_color);

		// Display keybinds
		{
			std::string infos = "Score: " + std::to_string(m_player->at(1).m_score);
			infos +=	"\nRotate: 'J' and 'L'\n"
						"Move: 'I'\n"
						"Shoot: 'K'\n"
						"Teleport: 'U' or 'O'\n";
			DrawAlignedText(infos.c_str(), 0.8f, m_screenWidth * 0.8f, m_screenHeight / 7.f, fontSize, WHITE);
		}
	}
}