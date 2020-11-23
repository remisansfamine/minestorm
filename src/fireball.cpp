#include "fireball.h"

#include "entity_manager.h"

#include "player.h"

#include "intersection.h"

Fireball::Fireball(const Referential2D& referential, Color color)
	: Projectile(referential, color)
{
	m_size = 0.225f * gameDifficulty;

	m_lifeTime = 8.f;

	m_translationSpeed = 75.f * gameDifficulty;

	Vector2D* target = nullptr;
	for (Player& player : entityManager->m_players)
	{
		if (!player.m_destroyed &&
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
		entityManager->m_fireballs.push_back(*this);
	}
}

void Fireball::update(float deltaTime)
{
	Projectile::update(deltaTime);

	Circle collider = getCircle();

	if (!intersect(collider, screenBorder))
	{
		m_destroyed = true;
		return;
	}

	for (Player& player : entityManager->m_players)
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

						m_destroyed = true;
						return;
					}
				}
			}
		}
	}
}