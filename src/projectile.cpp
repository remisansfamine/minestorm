#include "projectile.h"

#include "entity_manager.h"

Projectile::Projectile(const Vector2D& pos, const Vector2D& dir, Color color)
	: Entity(pos, dir)
{
	m_srcRect = { 768, 0, 256, 256 };
	m_color = color;

	m_translationSpeed = 500.f;
	m_speed = -m_referential.m_j * m_translationSpeed;

	m_entityManager->m_bullet.push_back(*this);
}

void Projectile::update(float deltaTime)
{
	move(deltaTime);
}


void Projectile::rotate(float deltaTime)
{
	
}

void Projectile::move(float deltaTime)
{
	m_referential.m_origin += m_speed * deltaTime;
}

void Projectile::drawDebug()
{
	Entity::drawDebug();
}