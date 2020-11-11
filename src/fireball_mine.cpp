#include "fireball_mine.h"

FireballMine::FireballMine(const Vector2D& pos, const Vector2D& dir)
	: Mine(pos, dir)
{
	m_srcRect = { 768, 256, 256, 256 };

	m_color = RED;
}