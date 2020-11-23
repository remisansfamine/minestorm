#include "floating_mine.h"

#include "entity_manager.h"

void FloatingMine::createCollider(float size)
{
	// Set the collider

	ConvexPolygon firstTriangle;
	firstTriangle.pts =
	{
		{ 0.f, -75.f * size },
		{ -15.f * size, -15.f * size },
		{ 0.f, 0.f },
		{ 15.f * size, -15.f * size },
	};

	ConvexPolygon secondTriangle;
	secondTriangle.pts =
	{
		{ 0.f, 0.f },
		{ -15.f * size, -15.f * size},
		{ -55.f * size, 35.f * size},
		{ 0.f, 20 * size}
	};

	ConvexPolygon thirdTriangle;
	thirdTriangle.pts =
	{
		{ 0.f, 20.f * size},
		{ 55.f * size, 35.f * size},
		{ 15.f * size, -15.f * size},
		{ 0.f, 0.f },
	};

	m_collider.polygon = { firstTriangle, secondTriangle, thirdTriangle };
}

FloatingMine::FloatingMine(int size)
	: Mine(size)
{
	m_score = 15 * (m_size * m_size) - 80 * m_size + 200;

	m_translationSpeed = 60.f / (m_size + 1.f) * gameDifficulty;

	m_srcRect = { 0, 256, 256, 256 };

	m_speed = -m_referential.m_j * m_translationSpeed;

	createCollider(m_size);
}

void FloatingMine::atDestroy()
{
	m_destroyed = true;

	if (m_mineSize == 0 || !entityManager->areCheckpointAvailable())
		return;

	new FloatingMine(m_mineSize - 1);
	new FloatingMine(m_mineSize - 1);
}