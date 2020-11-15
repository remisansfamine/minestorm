#include "projectile.h"

#include "entity_manager.h"

#include <iostream>

#include "mine.h"

Projectile::Projectile(const Referential2D& referential, Color color)
	: Entity(referential)
{
	m_srcRect = { 768, 0, 256, 256 };
	m_color = color;

	m_translationSpeed = 400.f;
	m_speed = -m_referential.m_j * m_translationSpeed;

	m_entityManager->m_projectile.push_back(this);
}

void Projectile::update(float deltaTime)
{
	move(deltaTime);

	Circle collider = getCircle();

	for (Mine* mine : m_entityManager->m_mine)
	{
		if (!mine)
			continue;

		ConcavePolygon polygonGlobal = mine->m_referential.concaveToGlobal(mine->m_collider);
		Rect AABB = polygonGlobal.getAABB();
		if (intersect(collider, AABB))
		{
			for (const ConvexPolygon& polygon : polygonGlobal.polygon)
			{
				AABB = polygon.getAABB();

				if (intersect(collider, AABB))
				{
					if (intersect(polygon, collider))
					{
						m_shouldBeDestroyed = mine->m_shouldBeDestroyed = true;
						break;
					}
				}
			}
		}
	}

	Rect rect = { Vector2D(320.f, 396.f), 259.f, 324.f };
	if (!intersect(collider, rect))
		m_shouldBeDestroyed = true;
}

void Projectile::rotate(float deltaTime) { }

void Projectile::move(float deltaTime)
{
	m_referential.m_origin += m_speed * deltaTime;
}

void Projectile::drawDebug() const
{
	Entity::drawDebug();

	DrawCircleLines(m_referential.m_origin.x, m_referential.m_origin.y, m_radius * m_size, ORANGE);
}

Circle Projectile::getCircle() const
{
	return { m_referential.m_origin, m_radius * m_size };
}