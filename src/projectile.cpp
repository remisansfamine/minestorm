#include "projectile.h"

#include "entity_manager.h"

#include "mine.h"

Projectile::Projectile(const Referential2D& referential, Color color)
	: Entity(referential)
{
	m_size = 0.5f;

	m_srcRect = { 768, 0, 256, 256 };
	m_color = color;
}

void Projectile::update(float deltaTime)
{
	m_lifeTime -= deltaTime;

	if (m_lifeTime <= 0)
	{
		m_shouldBeDestroyed = true;
		return;
	}

	move(deltaTime);

	stayInScreen();
}

void Projectile::rotate(float deltaTime) { }

void Projectile::move(float deltaTime)
{
	m_referential.m_origin += m_speed * deltaTime;
}

void Projectile::drawDebug() const
{
	Entity::drawDebug();

	Circle circle = getCircle();

	DrawCircleLines(circle.center.x, circle.center.y, circle.radius, ORANGE);
}

Circle Projectile::getCircle() const
{
	return { m_referential.m_origin, m_radius * m_size };
}