#include "spawn_point.h"

#include "entity_manager.h"

#include "particle.h"
#include "maths_utils.h"

SpawnPoint::SpawnPoint(Vector2D pos, bool isInitial)
	: m_isInitial(isInitial), m_spawnCooldown(isInitial ? 0.f : 0.75f),
	Entity(Referential2D(pos, Vector2D(1.f, 0.f)))
{
	m_size = 0.225f;

	m_srcRect = { 256, 0, 256, 256 };

	m_translationSpeed = 100.f;

	m_target = getRandomPosition();

	m_color = WHITE;

	entityManager->m_spawnPoints.push_back(*this);

	m_isAvailable = isInitial;

	for (int i = 0; i < 5; i++)
		Particle(m_referential, 0.005f, WHITE, randomVector() * 20.f);
}

void SpawnPoint::update(float deltaTime)
{
	// If the spawn point has been created by the Minelayer
	if (!m_isInitial)
	{
		// Check if it can spawn a mine at its position
		m_spawnCooldown -= deltaTime;
		if (m_spawnCooldown < 0.f)
			entityManager->spawnMine(this);
	}
	else
		move(deltaTime);
}

void SpawnPoint::move(float deltaTime)
{
	// Checking if the spawnpoint is available (if it is static)
	if (!m_isAvailable)
	{
		if (sqrDistance(m_referential.m_origin, m_target) <= 5.f)
			m_isAvailable = true;

		m_speed = (m_target - m_referential.m_origin).normalized() * m_translationSpeed;
		m_referential.m_origin += m_speed * deltaTime;
	}
}

void SpawnPoint::rotate(float deltaTime) { }