#include "magnetic_mine.h"

#include "entity_manager.h"

void MagneticMine::createCollider(float size)
{
	// Set the collider

	ConvexPolygon firstTriangle;
	firstTriangle.pts =
	{
		{ 0.f, 0.f },
		{ 0.f, 25.f * size },
		{ -50.f * size, 50.f * size },
		{ -25.f * size, 0.f }
	};

	ConvexPolygon secondTriangle;
	secondTriangle.pts =
	{
		{ 0.f, 0.f },
		{ -25.f * size, 0.f },
		{ -50.f * size, -50.f * size },
		{ 0.f, -25.f * size }
	};

	ConvexPolygon thirdTriangle;
	thirdTriangle.pts =
	{
		{ 0.f, 0.f },
		{ 0.f, -25.f * size },
		{ 50.f * size, -50.f * size },
		{ 25.f * size, 0.f }
	};

	ConvexPolygon forthTriangle;
	forthTriangle.pts =
	{
		{ 0.f, 0.f },
		{ 25.f * size, 0.f },
		{ 50.f * size, 50.f * size },
		{ 0.f, 25.f * size }
	};

	m_collider.polygon = { firstTriangle, secondTriangle, thirdTriangle, forthTriangle };
}

MagneticMine::MagneticMine(SpawnPoint* sp, int size)
	: Mine(size, sp)
{
	m_score = 15 * (m_size * m_size) - 80 * m_size + 600;

	m_translationSpeed = 60.f / (m_size + 1.f) * gameDifficulty;

	m_srcRect = { 256, 256, 256, 256 };

	createCollider(m_size);
}

void MagneticMine::getTarget()
{

	if (entityManager->m_players.size() == 0)
	{
		m_target = nullptr;
		return;
	}

	for (Player& player : entityManager->m_players)
	{
		if ((!m_target ||
			sqrDistance(m_referential.m_origin, player.m_referential.m_origin)
			< sqrDistance(m_referential.m_origin, m_target->m_referential.m_origin)) && !player.m_destroyed)
		{
			m_target = &player;
		}
	}
}

void MagneticMine::update(float deltaTime)
{
	getTarget();

	if (m_target)
		m_speed = getInScreenDirection(m_target->m_referential.m_origin) * m_translationSpeed;

	Mine::update(deltaTime);
}

void MagneticMine::atDestroy()
{
	m_destroyed = true;

	if (m_mineSize == 0 || !entityManager->areCheckpointAvailable())
		return;

	new MagneticMine(nullptr, m_mineSize - 1);
	new MagneticMine(nullptr, m_mineSize - 1);
}