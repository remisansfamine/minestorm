#include "magnetic_fireball_mine.h"

void MagneticFireballMine::createCollider(int size)
{
	ConvexPolygon base;
	base.pts =
	{
		{ -44.f * m_size, -44.f * m_size },
		{ -44.f * m_size, 44.f * m_size },
		{ 44.f * m_size, 44.f * m_size },
		{ 44.f * m_size, -44.f * m_size },
	};

	ConvexPolygon firstTriangle;
	firstTriangle.pts =
	{
		{ -44.f * m_size, -44.f * m_size },
		{ -44.f * m_size, -75.f * m_size },
		{ -30.f * m_size, -44.f * m_size },
	};

	ConvexPolygon secondTriangle;
	secondTriangle.pts =
	{
		{ -44.f * m_size, 44.f * m_size },
		{ -75.f * m_size, 44.f * m_size },
		{ -44.f * m_size, 30.f * m_size },
	};

	ConvexPolygon thirdTriangle;
	thirdTriangle.pts =
	{
		{ 44.f * m_size, 44.f * m_size },
		{ 44.f * m_size, 75.f * m_size },
		{ 30.f * m_size, 44.f * m_size },
	};

	ConvexPolygon forthTriangle;
	forthTriangle.pts =
	{
		{ 44.f * m_size, -44.f * m_size },
		{ 75.f * m_size, -44.f * m_size },
		{ 44.f * m_size, -30.f * m_size },
	};

	m_collider.polygon = { firstTriangle, secondTriangle, thirdTriangle, forthTriangle, base };
}

MagneticFireballMine::MagneticFireballMine(const Referential2D& referential)
	: Mine(referential)
{
	m_srcRect = { 512, 256, 256, 256 };

	m_color = RED;

	createCollider();
}