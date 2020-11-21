#include "spawn_point.h"

#include "entity_manager.h"

SpawnPoint::SpawnPoint(Vector2D pos, bool isAvailable)
	: m_isAvailable(isAvailable), Entity(Referential2D(pos, Vector2D(1.f, 0.f)))
{
	m_size = 0.5f;

	m_srcRect = { 256, 0, 256, 256 };

	m_translationSpeed = 100.f;

	m_target = screenBorder.pt + Vector2D(randomNumber(-screenBorder.halfWidth, screenBorder.halfWidth),
										  randomNumber(-screenBorder.halfHeight, screenBorder.halfHeight));

	m_color = WHITE;

	entityManager->m_spawnPoint.push_back(*this);
}

void SpawnPoint::update(float deltaTime)
{
	move(deltaTime);
}

void SpawnPoint::move(float deltaTime)
{
	if (!m_isAvailable)
	{
		if (sqrDistance(m_referential.m_origin, m_target) <= 5.f)
			m_isAvailable = true;

		m_speed = (m_target - m_referential.m_origin).normalized() * m_translationSpeed;
		m_referential.m_origin += m_speed * deltaTime;
	}
}

void SpawnPoint::rotate(float deltaTime)
{

}