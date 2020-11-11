#include "magnetic_fireball_mine.h"

MagneticFireballMine::MagneticFireballMine(const Vector2D& pos, const Vector2D& dir)
	: Mine(pos, dir)
{
	m_srcRect = { 512, 256, 256, 256 };

	m_color = RED;
}