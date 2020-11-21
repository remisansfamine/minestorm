#include "entity.h"

#include "entity_manager.h"

EntityManager*	Entity::entityManager;
Rect			Entity::screenBorder = { { 320.f, 396.f }, 259.f, 324.f };

Entity::Entity(const Referential2D& referential)
	: m_referential(referential)
{ }
	
void Entity::stayInScreen()
{
	int offset = 10;
	if (m_referential.m_origin.x < 62 - offset)
		m_referential.m_origin.x = 580;

	else if (m_referential.m_origin.x > 580 + offset)
		m_referential.m_origin.x = 62;

	if (m_referential.m_origin.y < 62 - offset)
		m_referential.m_origin.y = 710;

	else if (m_referential.m_origin.y > 710 + offset)
		m_referential.m_origin.y = 64;
}

void Entity::draw(const Texture2D& spriteSheet) const
{
	float textureSize = 256.f * (0.15f * m_size + 0.15f);
	Vector2 origin =  Vector2D(0.5f, 0.5f) * textureSize;
	Rectangle destRect = { m_referential.m_origin.x, m_referential.m_origin.y, textureSize, textureSize };
	DrawTexturePro(spriteSheet, m_srcRect, destRect, origin, m_referential.m_angle * 180.f / M_PI, m_color);
}

void Entity::drawDebug() const
{
	Vector2D pos = m_referential.m_origin;

	Vector2D i = m_referential.m_origin + m_referential.m_i * 100.f;
	DrawLine(pos.x, pos.y, i.x, i.y, RED);

	Vector2D j = m_referential.m_origin - m_referential.m_j * 100.f;
	DrawLine(pos.x, pos.y, j.x, j.y, GREEN);

	Vector2D speed = m_referential.m_origin + m_speed;
	DrawLine(pos.x, pos.y, speed.x, speed.y, BLUE);

	Vector2D acceleration = m_referential.m_origin + m_acceleration;
	DrawLine(pos.x, pos.y, acceleration.x, acceleration.y, RAYWHITE);
}