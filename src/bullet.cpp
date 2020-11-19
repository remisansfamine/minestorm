#include "bullet.h"

#include "entity_manager.h"

#include "mine.h"

#include "player.h"

#include "fireball.h"

#include <iostream>

Bullet::Bullet(const Referential2D& referential, Color color, Player* owner)
	: m_owner(owner), Projectile(referential, color)
{
	m_translationSpeed = 500.f;

	m_speed = -m_referential.m_j * m_translationSpeed;

	m_lifeTime = 1.5f;

	entityManager->m_bullet.push_back(*this);
}

void Bullet::update(float deltaTime)
{
	Projectile::update(deltaTime);

	Circle collider = getCircle();

	for (Mine* mine : entityManager->m_mine)
	{
		if (!mine || mine->m_shouldBeDestroyed)
			continue;

		ConcavePolygon polygonGlobal = mine->m_referential.concaveToGlobal(mine->m_collider);
		Rect AABB = polygonGlobal.getAABB();
		if (intersect(polygonGlobal, collider))
		{
			if (m_owner)
				m_owner->m_score += mine->m_score;

			m_shouldBeDestroyed = true;

			mine->atDestroy();

			return;
		}
	}

	for (Fireball& fireball : entityManager->m_fireball)
	{
		if (fireball.m_shouldBeDestroyed)
			continue;

		if (intersect(fireball.getCircle(), collider))
		{
			if (m_owner)
				m_owner->m_score += fireball.m_score;

			m_shouldBeDestroyed = fireball.m_shouldBeDestroyed = true;

			return;
		}
	}
}