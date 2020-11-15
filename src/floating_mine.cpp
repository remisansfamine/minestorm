#include "floating_mine.h"

void FloatingMine::createCollider(int size)
{
	ConvexPolygon firstTriangle;
	firstTriangle.pts =
	{
		{ 0, -73 * 0.5f },
		{ -18 * m_size, -15 * m_size },
		{ 0, 0 },
		{ 17 * m_size, -15 * m_size },
	};

	ConvexPolygon secondTriangle;
	secondTriangle.pts =
	{
		{ 0, 0 },
		{ -18 * m_size, -15 * m_size},
		{ -56 * m_size, 33 * m_size},
		{ 0, 21 * m_size}
	};

	ConvexPolygon thirdTriangle;
	thirdTriangle.pts =
	{
		{ 0, 21 * m_size},
		{ 56 * m_size, 33 * m_size},
		{ 17 * m_size, -15 * m_size},
		{ 0, 0 },
	};

	m_collider.polygon = { firstTriangle, secondTriangle, thirdTriangle };
}

FloatingMine::FloatingMine(const Referential2D& referential)
	: Mine(referential)
{
	m_srcRect = { 0, 256, 256, 256 };

	m_color = RED;

	createCollider(1);

	m_translationSpeed = 150.f;

	m_speed = -m_referential.m_j * m_translationSpeed;
}