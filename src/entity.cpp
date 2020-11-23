#include "entity.h"

#include "entity_manager.h"

#include "maths_utils.h"

#define SCREENOFFSET 10.f

EntityManager*	Entity::entityManager;
Rect			Entity::screenBorder = { { 320.f, 396.f }, 259.f, 324.f };
float			Entity::gameDifficulty = 1.f;

Entity::Entity(const Referential2D& referential)
	: m_referential(referential)
{ }

Vector2D Entity::getRandomPosition()
{
	// Get a random position in the screen
	return screenBorder.pt + Vector2D(randomNumber(-screenBorder.halfWidth + SCREENOFFSET, screenBorder.halfWidth - SCREENOFFSET),
									  randomNumber(-screenBorder.halfHeight + SCREENOFFSET, screenBorder.halfHeight - SCREENOFFSET));
}

Vector2D Entity::getInScreenDirection(Vector2D target)
{
	// Get the direction between the target and the entity
	Vector2D m_direction = target - m_referential.m_origin;

	// Take the shortest path by checking if the passage through the edge of the screen is effective
	if (abs(m_direction.x) > screenBorder.halfWidth)
		m_direction.x *= -1.f;

	if (abs(m_direction.y) > screenBorder.halfHeight)
		m_direction.y *= -1.f;

	return m_direction.normalized();
}

void Entity::stayInScreen()
{
	if (m_referential.m_origin.x < 62)
		m_referential.m_origin.x = 580;

	if (m_referential.m_origin.x > 580)
		m_referential.m_origin.x = 62;

	if (m_referential.m_origin.y < 62)
		m_referential.m_origin.y = 710;

	if (m_referential.m_origin.y > 710)
		m_referential.m_origin.y = 64;
}

void Entity::draw(const Texture2D& spriteSheet) const
{
	float textureSize = 256.f * m_size;
	Vector2 origin =  Vector2D(0.5f, 0.5f) * textureSize;
	Rectangle destRect = { m_referential.m_origin.x, m_referential.m_origin.y, textureSize, textureSize };

	DrawTexturePro(spriteSheet, m_srcRect, destRect, origin, m_referential.m_angle * radToDeg(), m_color);
}

void Entity::drawDebug() const
{
	Vector2D pos = m_referential.m_origin;

	// Draw the direction vectors
	Vector2D i = m_referential.m_origin + m_referential.m_i * 100.f;
	DrawLine(pos.x, pos.y, i.x, i.y, RED);

	Vector2D j = m_referential.m_origin - m_referential.m_j * 100.f;
	DrawLine(pos.x, pos.y, j.x, j.y, GREEN);

	// Draw the speed and acceleration vectors
	Vector2D speed = m_referential.m_origin + m_speed;
	DrawLine(pos.x, pos.y, speed.x, speed.y, BLUE);

	Vector2D acceleration = m_referential.m_origin + m_acceleration;
	DrawLine(pos.x, pos.y, acceleration.x, acceleration.y, RAYWHITE);
}