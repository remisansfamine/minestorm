#include "magnetic_fireball_mine.h"

#include "entity_manager.h"

#include "fireball.h"

void MagneticFireballMine::createCollider(float size)
{
	ConvexPolygon base;
	base.pts =
	{
		{ -45.f * size, -45.f * size },
		{ -45.f * size, 45.f * size },
		{ 45.f * size, 45.f * size },
		{ 45.f * size, -45.f * size },
	};

	ConvexPolygon firstTriangle;
	firstTriangle.pts =
	{
		{ -45.f * size, -45.f * size },
		{ -45.f * size, -75.f * size },
		{ -30.f * size, -45.f * size },
	};

	ConvexPolygon secondTriangle;
	secondTriangle.pts =
	{
		{ -45.f * size, 45.f * size },
		{ -75.f * size, 45.f * size },
		{ -45.f * size, 30.f * size },
	};

	ConvexPolygon thirdTriangle;
	thirdTriangle.pts =
	{
		{ 45.f * size, 45.f * size },
		{ 45.f * size, 75.f * size },
		{ 30.f * size, 45.f * size },
	};

	ConvexPolygon forthTriangle;
	forthTriangle.pts =
	{
		{ 45.f * size, -45.f * size },
		{ 75.f * size, -45.f * size },
		{ 45.f * size, -30.f * size },
	};

	m_collider.polygon = { firstTriangle, secondTriangle, thirdTriangle, forthTriangle, base };
}

MagneticFireballMine::MagneticFireballMine(int size)
	: Mine()
{
	m_size = size;

	m_score = 15 * (m_size * m_size) - 80 * m_size + 850;

	m_translationSpeed = 60.f / m_size;

	m_srcRect = { 512, 256, 256, 256 };

	createCollider(0.25f * m_size + 0.25f);
}

void MagneticFireballMine::getTarget()
{
	if (entityManager->m_player.size() == 0)
	{
		m_target = nullptr;
		return;
	}

	for (Player& player : entityManager->m_player)
	{
		if (!m_target ||
			sqrDistance(m_referential.m_origin, player.m_referential.m_origin) < sqrDistance(m_referential.m_origin, m_target->m_referential.m_origin))
			m_target = &player;
	}
}

void MagneticFireballMine::update(float deltaTime)
{
	getTarget();

	if (m_target)
		m_speed = (m_target->m_referential.m_origin - m_referential.m_origin).normalized() * m_translationSpeed;

	Mine::update(deltaTime);
}

void MagneticFireballMine::atDestroy()
{
	Fireball(m_referential, ORANGE);

	m_shouldBeDestroyed = true;

	if (m_size == 0 || !entityManager->areCheckpointAvailable())
		return;

	new MagneticFireballMine(m_size - 1);
	new MagneticFireballMine(m_size - 1);
}