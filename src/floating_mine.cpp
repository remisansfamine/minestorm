#include "floating_mine.h"

FloatingMine::FloatingMine(const Vector2D& pos, const Vector2D& dir)
	: Mine(pos, dir)
{
	m_srcRect = { 0, 256, 256, 256 };

	m_color = RED;
}