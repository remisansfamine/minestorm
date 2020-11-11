#include "entity.h"

#include "entity_manager.h"

EntityManager* Entity::m_entityManager;

Entity::Entity(const Vector2D& pos, const Vector2D& dir)
	: m_referential(pos, dir)
{
	
}
	
void Entity::stayInScreen()
{
	if (m_referential.m_origin.x <= 62)
		m_referential.m_origin.x = 580;
	else if (m_referential.m_origin.x >= 580)
		m_referential.m_origin.x = 62;

	if (m_referential.m_origin.y <= 62)
		m_referential.m_origin.y = 710;
	else if (m_referential.m_origin.y >= 710)
		m_referential.m_origin.y = 64;
}

void Entity::draw(const Texture2D& spriteSheet)
{
	float textureSize = 256.f * m_size;
	Vector2 origin =  Vector2D(0.5f, 0.5f) * textureSize;
	Rectangle destRect = { m_referential.m_origin.x, m_referential.m_origin.y, textureSize, textureSize };
	DrawTexturePro(spriteSheet, m_srcRect, destRect, origin, m_referential.m_angle, m_color);
}

void Entity::drawDebug()
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