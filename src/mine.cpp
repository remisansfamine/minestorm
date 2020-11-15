#include "mine.h"

#include <iostream>

#include "entity_manager.h"

Mine::Mine(const Referential2D& referential)
	: Entity(referential)
{
	m_entityManager->m_mine.push_back(this);


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

		for (unsigned int i = 0; i < polygon.pts.size(); i++)
		{
			unsigned int j = (i + 1) % polygon.pts.size();

			Vector2D point0 = polygon.pts[i];
			Vector2D point1 = polygon.pts[j];

			DrawCircle(point0.x, point0.y, 2, BLACK);
			DrawLine(point0.x, point0.y, point1.x, point1.y, ORANGE);
		}
	}
}