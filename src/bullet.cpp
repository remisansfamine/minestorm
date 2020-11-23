#include "bullet.h"

#include "entity_manager.h"

#include "mine.h"
#include "player.h"
#include "fireball.h"

#include "intersection.h"

Bullet::Bullet(const Referential2D& referential, Color color, Player* owner)
	: m_owner(owner), Projectile(referential, color)
{
	m_size = 0.225f;

	m_translationSpeed = 500.f;

	m_speed = -m_referential.m_j * m_translationSpeed;

	m_lifeTime = 0.9f;

	entityManager->m_bullets.push_back(*this);
}

void Bullet::update(float deltaTime)
{
	Projectile::update(deltaTime);

	m_collider = getCircle();

	stayInScreen();

	checkCollisionMinelayer();
	checkCollisionMine();
	checkCollisionFireball();
}

void Bullet::checkCollisionMinelayer()
{
	if (m_destroyed)
		return;

	if (!entityManager->m_minelayer.m_destroyed)
	{
		Minelayer& minelayer = entityManager->m_minelayer;
		ConcavePolygon	polygonGlobal = minelayer.m_referential.concaveToGlobal(minelayer.m_collider);
		Rect			AABB = polygonGlobal.getAABB();

		if (intersect(polygonGlobal, m_collider))
		{
			// Set the score to the player and destroy the Minelayer and the bullet
			if (m_owner)
				m_owner->m_score += minelayer.m_score;

			m_destroyed = minelayer.m_destroyed = true;
		}
	}
}

void Bullet::checkCollisionMine()
{
	if (m_destroyed)
		return;

	for (Mine* mine : entityManager->m_mines)
	{
		if (!mine || mine->m_destroyed)
			continue;

		ConcavePolygon polygonGlobal = mine->m_referential.concaveToGlobal(mine->m_collider);
		Rect AABB = polygonGlobal.getAABB();
		if (intersect(polygonGlobal, m_collider))
		{
			// Set the score to the player and destroy the mine and the bullet

			if (m_owner)
				m_owner->m_score += mine->m_score;

			m_destroyed = true;

			mine->atDestroy();

			return;
		}
	}
}

void Bullet::checkCollisionFireball()
{
	if (m_destroyed)
		return;

	for (Fireball& fireball : entityManager->m_fireballs)
	{
		if (fireball.m_destroyed)
			continue;

		if (intersect(fireball.getCircle(), m_collider))
		{
			// Set the score to the player and destroy the fireball and the bullet

			if (m_owner)
				m_owner->m_score += fireball.m_score;

			m_destroyed = fireball.m_destroyed = true;

			return;
		}
	}
}