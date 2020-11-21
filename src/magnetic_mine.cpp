#include "magnetic_mine.h"

#include "entity_manager.h"

void MagneticMine::createCollider(float size)
{
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

MagneticMine::MagneticMine(int size)
	: Mine()
{
	m_size = size;

	m_score = 15 * (m_size * m_size) - 80 * m_size + 600;

	m_translationSpeed = 60.f / m_size;

	m_srcRect = { 256, 256, 256, 256 };

	createCollider(0.15f * m_size + 0.15f);
}

void MagneticMine::getTarget()
{

	if (entityManager->m_player.size() == 0)
	{
		m_target = nullptr;
		return;
	}

	for (Player& player : entityManager->m_player)
	{
		if (!m_target ||
			distance(m_referential.m_origin, player.m_referential.m_origin)
			< distance(m_referential.m_origin, m_target->m_referential.m_origin))
		{
			m_target = &player;
		}
	}
}

void MagneticMine::update(float deltaTime)
{
	getTarget();

	if (m_target)
	{
		Vector2D m_direction = (m_target->m_referential.m_origin - m_referential.m_origin);

		m_direction.x *= sign(screenBorder.halfWidth - abs(m_direction.x));
		m_direction.y *= sign(screenBorder.halfHeight - abs(m_direction.y));

		m_speed = m_direction.normalized() * m_translationSpeed;
	}

	Mine::update(deltaTime);
}

void MagneticMine::atDestroy()
{
	m_shouldBeDestroyed = true;

	if (m_size == 0 || !entityManager->areCheckpointAvailable())
		return;

	new MagneticMine(m_size - 1);
	new MagneticMine(m_size - 1);
}