#include "fireball.h"

#include "entity_manager.h"

#include "player.h"

Fireball::Fireball(const Referential2D& referential, Color color)
	: Projectile(referential, color)
{
	m_lifeTime = 8.f;

	m_translationSpeed = 75.f;

	Vector2D* target = nullptr;
	for (Player& player : entityManager->m_player)
	{
		if (!player.m_shouldBeDestroyed &&
		   (!target ||
			sqrDistance(m_referential.m_origin, player.m_referential.m_origin)
			< sqrDistance(m_referential.m_origin, *target)))
		{
			target = &player.m_referential.m_origin;
		}
	}

	if (target)
	{
		m_speed = (*target - m_referential.m_origin).normalized() * m_translationSpeed;
		entityManager->m_fireball.push_back(*this);
	}
}

void Fireball::update(float deltaTime)
{
	Projectile::update(deltaTime);

	Circle collider = getCircle();

	for (Player& player : entityManager->m_player)
	{
		ConcavePolygon polygonGlobal = player.m_referential.concaveToGlobal(player.m_collider);
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
						player.hurt();

						m_shouldBeDestroyed = true;
						return;
					}
				}
			}
		}
	}
}