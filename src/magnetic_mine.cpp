#include "magnetic_mine.h"

MagneticMine::MagneticMine(const Vector2D& pos, const Vector2D& dir)
	: Mine(pos, dir)
{
	m_srcRect = { 256, 256, 256, 256 };

	m_color = RED;
}