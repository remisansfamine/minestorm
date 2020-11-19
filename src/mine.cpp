#include "mine.h"

#include <iostream>

#include "spawn_point.h"

#include "entity_manager.h"

Mine::Mine()
{
	m_rotationSpeed = 2.5f;

	m_color = RED;

	SpawnPoint* spawn;
	do
	{
		spawn = &entityManager->m_spawnPoint.at(rand() % entityManager->m_spawnPoint.size());
	} while (!spawn->m_isAvailable && !spawn->m_shouldBeDestroyed && !spawn->m_isReserved);

	float x = randomNumber(-1.f, 1.f);
	float y = randomNumber(-1.f, 1.f);

	m_referential = Referential2D(spawn->m_referential.m_origin, Vector2D(x, y));

	spawn->m_shouldBeDestroyed = true;

	entityManager->m_mine.push_back(this);
}

void Mine::update(float deltaTime)
{
	//move(deltaTime);
	//rotate(deltaTime);
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

	DrawRectangleLines(concaveAABB.pt.x - concaveAABB.halfWidth,
					   concaveAABB.pt.y - concaveAABB.halfHeight,
					   concaveAABB.halfWidth * 2.f,
					   concaveAABB.halfHeight * 2.f,
					   PINK);

	for (const ConvexPolygon& polygon : polygonGlobal.polygon)
	{
		Rect  convexAABB = polygon.getAABB();

		DrawRectangleLines(convexAABB.pt.x - convexAABB.halfWidth,
			convexAABB.pt.y - convexAABB.halfHeight,
			convexAABB.halfWidth * 2.f,
			convexAABB.halfHeight * 2.f,
			BLUE);

		for (int i = 0; i < polygon.pts.size(); i++)
		{
			int j = (i + 1) % polygon.pts.size();

			Vector2D point0 = polygon.pts[i];
			Vector2D point1 = polygon.pts[j];

			DrawCircle(point0.x, point0.y, 2, BLACK);
			DrawLine(point0.x, point0.y, point1.x, point1.y, ORANGE);
		}
	}
}