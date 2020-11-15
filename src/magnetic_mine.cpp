#include "magnetic_mine.h"

void MagneticMine::createCollider(int size)
{
	ConvexPolygon firstTriangle;
	firstTriangle.pts =
	{
		{ 0.f, 0.f },
		{ 0.f, 25.f * 0.5f },
		{ -48.f * 0.5f, 48.f * 0.5f },
		{ -25.f * 0.5f, 0.f }
	};

	ConvexPolygon secondTriangle;
	secondTriangle.pts =
	{
		{ 0.f, 0.f },
		{ -25.f * m_size, 0.f },
		{ -48.f * m_size, -48.f * m_size },
		{ 0.f, -25.f * m_size }
	};

	ConvexPolygon thirdTriangle;
	thirdTriangle.pts =
	{
		{ 0.f, 0.f },
		{ 0.f, -25.f * m_size },
		{ 48.f * m_size, -48.f * m_size },
		{ 25.f * m_size, 0.f }
	};

	ConvexPolygon forthTriangle;
	forthTriangle.pts =
	{
		{ 0.f, 0.f },
		{ 25.f * m_size, 0.f },
		{ 48.f * m_size, 50.f * m_size },
		{ 0.f, 25.f * m_size }
	};

	m_collider.polygon = { firstTriangle, secondTriangle, thirdTriangle, forthTriangle };
}

MagneticMine::MagneticMine(const Referential2D& referential)
	: Mine(referential)
{
	m_srcRect = { 256, 256, 256, 256 };

	m_color = RED;

	createCollider();
}