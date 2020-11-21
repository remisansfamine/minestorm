#include "fireball_mine.h"

#include "fireball.h"

#include "entity_manager.h"

#include <iostream>

void FireballMine::createCollider(float size)
{
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

FireballMine::FireballMine(int size)
	: Mine()
{
	m_size = size;

	m_score = 15 * (m_size * m_size) - 80 * m_size + 425;

	m_translationSpeed = 40.f / m_size;

	m_speed = -m_referential.m_j * m_translationSpeed;

	m_srcRect = { 768, 256, 256, 256 };

	createCollider(0.15f * m_size + 0.15f);
}

void FireballMine::atDestroy()
{
	Fireball(m_referential, ORANGE);

	m_shouldBeDestroyed = true;

	if (m_size == 0 || !entityManager->areCheckpointAvailable())
		return;

	new FireballMine(m_size - 1);
	new FireballMine(m_size - 1);
}