#include "fireball_mine.h"

#include "fireball.h"

#include "entity_manager.h"

void FireballMine::createCollider(float size)
{
	// Set the collider

	ConvexPolygon firstTriangle;
	firstTriangle.pts =
	{
		{ 0.f, 0.f },
		{ 0.f, 40.f * size },
		{ -50.f * size, 50.f * size },
		{ -40.f * size, 0.f }
	};

	ConvexPolygon secondTriangle;
	secondTriangle.pts =
	{
		{ 0.f, 0.f },
		{ -40.f * size, 0.f },
		{ -50.f * size, -50.f * size },
		{ 0.f, -40.f * size }
	};

	ConvexPolygon thirdTriangle;
	thirdTriangle.pts =
	{
		{ 0.f, 0.f },
		{ 0.f, -40.f * size },
		{ 50.f * size, -50.f * size },
		{ 40.f * size, 0.f }
	};

	ConvexPolygon forthTriangle;
	forthTriangle.pts =
	{
		{ 0.f, 0.f },
		{ 38.f * size, 0.f },
		{ 50.f * size, 50.f * size },
		{ 0.f, 38.f * size }
	};

	m_collider.polygon = { firstTriangle, secondTriangle, thirdTriangle, forthTriangle };
}

FireballMine::FireballMine(SpawnPoint* sp, int size)
	: Mine(size, sp)
{
	m_score = (15 * size - 80) * size + 425;

	m_translationSpeed = 40.f / (m_size + 1.f) * gameDifficulty;

	m_speed = -m_referential.m_j * m_translationSpeed;

	m_srcRect = { 768, 256, 256, 256 };

	createCollider(m_size);
}

void FireballMine::atDestroy()
{
	Fireball(m_referential, ORANGE);

	m_destroyed = true;

	if (m_mineSize == 0 || !entityManager->areCheckpointAvailable())
		return;

	new FireballMine(nullptr, m_mineSize - 1);
	new FireballMine(nullptr, m_mineSize - 1);
}