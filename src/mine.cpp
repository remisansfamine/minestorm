#include "mine.h"

#include "spawn_point.h"

#include "entity_manager.h"

#include "particle.h"
#include "maths_utils.h"

Mine::Mine(int size, SpawnPoint* sp)
{
	m_mineSize = size;

	m_size = (0.15f * (size + 1.f)) * gameDifficulty;

	m_rotationSpeed = 2.5f;

	m_color = RED;

	if (!sp)
	{
		// If there is no spawn point assigned
		// get a random spawnpoint to spawn at its position
		do
		{
			sp = &entityManager->m_spawnPoints.at(rand() % entityManager->m_spawnPoints.size());
		} while (!sp->m_isAvailable || sp->m_destroyed || !sp->m_isInitial);
	}

	m_referential = Referential2D(sp->m_referential.m_origin, randomVector());

	sp->m_destroyed = true;

	// Create particles at creation
	for (int i = 0; i < 5; i++)
		Particle(m_referential, 0.005f, WHITE, randomVector() * 30.f, true);

	entityManager->m_mines.push_back(this);
}

void Mine::update(float deltaTime)
{
	move(deltaTime);
	rotate(deltaTime);
}

void Mine::move(float deltaTime)
{
	m_referential.m_origin += m_speed * deltaTime;

	stayInScreen();
}

void Mine::rotate(float deltaTime)
{
	m_referential.rotate(deltaTime * m_rotationSpeed);
}

void Mine::drawDebug() const
{
	Entity::drawDebug();

	ConcavePolygon polygonGlobal = m_referential.concaveToGlobal(m_collider);

	Rect concaveAABB = polygonGlobal.getAABB();

	concaveAABB.drawDebug();

	for (const ConvexPolygon& polygon : polygonGlobal.polygon)
		polygon.drawDebug();
}

void Mine::atDestroy()
{
	m_destroyed = true;

	for (int i = 0; i < 5; i++)
		Particle(m_referential, 0.005f, RED, randomVector() * 50.f);
}