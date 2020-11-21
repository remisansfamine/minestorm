#include "mine.h"

#include <iostream>

#include "spawn_point.h"

#include "entity_manager.h"

Mine::Mine()
{
	entityManager->m_mine.push_back(this);

	m_rotationSpeed = 2.5f;

	m_color = RED;

	SpawnPoint* spawn;
	do
	{
		spawn = &entityManager->m_spawnPoint.at(rand() % entityManager->m_spawnPoint.size());
	} while (!spawn->m_isAvailable || spawn->m_shouldBeDestroyed || spawn->m_isReserved);

	float x = randomNumber(-1.f, 1.f);
	float y = randomNumber(-1.f, 1.f);

	m_referential = Referential2D(spawn->m_referential.m_origin, Vector2D(x, y));

	spawn->m_shouldBeDestroyed = true;
}

void Mine::update(float deltaTime)
{
	move(deltaTime);
	rotate(deltaTime);
}

void Mine::move(float deltaTime)
{
	m_referential.m_origin += m_speed * deltaTime;

	stayInScreen();
}

void Mine::rotate(float deltaTime)
{
	m_referential.rotate(deltaTime * m_rotationSpeed);
}

void Mine::drawDebug() const
{
	Entity::drawDebug();

	ConcavePolygon polygonGlobal = m_referential.concaveToGlobal(m_collider);

	Rect concaveAABB = polygonGlobal.getAABB();

	concaveAABB.drawDebug();

	for (const ConvexPolygon& polygon : polygonGlobal.polygon)
		polygon.drawDebug();
}