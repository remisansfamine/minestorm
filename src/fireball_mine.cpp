#include "fireball_mine.h"

void FireballMine::createCollider(int size)
{
	ConvexPolygon firstTriangle;
	firstTriangle.pts =
	{
		{ 0.f, 0.f },
		{ 0.f, 38.f * m_size },
		{ -50.f * m_size, 50.f * m_size },
		{ -38.f * m_size, 0.f }
	};

	ConvexPolygon secondTriangle;
	secondTriangle.pts =
	{
		{ 0.f, 0.f },
		{ -38.f * m_size, 0.f },
		{ -50.f * m_size, -50.f * m_size },
		{ 0.f, -38.f * m_size }
	};

	ConvexPolygon thirdTriangle;
	thirdTriangle.pts =
	{
		{ 0.f, 0.f },
		{ 0.f, -38.f * m_size },
		{ 50.f * m_size, -50.f * m_size },
		{ 38.f * m_size, 0.f }
	};

	ConvexPolygon forthTriangle;
	forthTriangle.pts =
	{
		{ 0.f, 0.f },
		{ 38.f * m_size, 0.f },
		{ 50.f * m_size, 50.f * m_size },
		{ 0.f, 38.f * m_size }
	};

	m_collider.polygon = { firstTriangle, secondTriangle, thirdTriangle, forthTriangle };
}

FireballMine::FireballMine(const Referential2D& referential)
	: Mine(referential)
{
	m_srcRect = { 768, 256, 256, 256 };

	m_translationSpeed = 150.f;

	m_color = RED;

	createCollider();
}