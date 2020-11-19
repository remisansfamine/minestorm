#include "entity_manager.h"

#include "projectile.h"

#include "floating_mine.h"
#include "fireball_mine.h"
#include "magnetic_mine.h"
#include "magnetic_fireball_mine.h"

#include "spawn_point.h"

#include <iostream>

#include <algorithm>

EntityManager::EntityManager(int playerCount)
{
	Entity::entityManager = this;

	m_spriteSheet = LoadTexture("assets/minestorm_sprite_atlas_mine_storm.png");

	m_input[0] = { KEY_R, KEY_D, KEY_G, KEY_F, KEY_E, KEY_T };
	m_input[1] = { KEY_I, KEY_J, KEY_L, KEY_K, KEY_U, KEY_O };
	m_input[2] = { KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_RIGHT_CONTROL, KEY_KP_0 };
	m_input[3] = { KEY_KP_8, KEY_KP_4, KEY_KP_6, KEY_KP_5, KEY_KP_7, KEY_KP_9 };
}

void EntityManager::setPlayerCount(int count)
{
	Color color[4] = { LIME, BLUE, WHITE, PINK };

	for (int i = 0; i < count; i++)
	{
		float x = Entity::screenBorder.pt.x - Entity::screenBorder.halfWidth * 0.5f * powf(-1, i);
		float y = Entity::screenBorder.pt.y;

		Player(i, m_input[i], Referential2D(Vector2D(x, y)), color[i]);
	}
}

EntityManager::~EntityManager()
{
	UnloadTexture(m_spriteSheet);

	for (Mine* mine : m_mine)
		delete mine;
}

void EntityManager::changeWave()
{
	wave++;
	for (int i = 0; i < 14; i++)
		SpawnPoint();
}

void EntityManager::spawnMine()
{
	int type = rand() % 4;
	switch (type)
	{
		case 0:
			new FloatingMine();
			break;
		case 1:
			new FireballMine();
			break;
		case 2:
			new MagneticMine();
			break;
		case 3:
			new MagneticFireballMine();
			break;

		default:
			new FloatingMine();
	}
}

void EntityManager::update(float deltaTime)
{
	if (m_spawnPoint.size() == 0 && m_mine.size() == 0)
		changeWave();

	if (areCheckpointAvailable(7))
		spawnMine();

	for (SpawnPoint& spawnPoint : m_spawnPoint)
		spawnPoint.update(deltaTime);

	for (Bullet& bullet : m_bullet)
		bullet.update(deltaTime);

	for (Fireball& fireball : m_fireball)
		fireball.update(deltaTime);

	for (Player& player : m_player)
		player.update(deltaTime);

	for (Mine* mine : m_mine)
	{
		if (mine && !mine->m_shouldBeDestroyed)
			mine->update(deltaTime);
	}

	clear();
}

void EntityManager::clear()
{
	m_spawnPoint.erase(std::remove_if(m_spawnPoint.begin(),
		m_spawnPoint.end(),
		[](const SpawnPoint& x) { return x.m_shouldBeDestroyed; }),
		m_spawnPoint.end());

	m_player.erase(std::remove_if(m_player.begin(),
		m_player.end(),
		[](const Player& x) { return x.m_shouldBeDestroyed; }),
		m_player.end());

	m_bullet.erase(std::remove_if(m_bullet.begin(),
		m_bullet.end(),
		[](const Bullet& x) { return x.m_shouldBeDestroyed; }),
		m_bullet.end());

	m_fireball.erase(std::remove_if(m_fireball.begin(),
		m_fireball.end(),
		[](const Fireball& x) { return x.m_shouldBeDestroyed; }),
		m_fireball.end());

	for (auto& minePtr : m_mine)
	{
		if (minePtr->m_shouldBeDestroyed)
		{
			delete minePtr;
			minePtr = nullptr;
		}
	}
	m_mine.erase(std::remove(m_mine.begin(), m_mine.end(), nullptr), m_mine.end());
}

void EntityManager::draw(bool isDebugging) const
{
	for (const SpawnPoint& spawnPoint : m_spawnPoint)
		spawnPoint.draw(m_spriteSheet);

	for (const Player& player : m_player)
		player.draw(m_spriteSheet);

	for (const Bullet& bullet : m_bullet)
		bullet.draw(m_spriteSheet);

	for (const Fireball& fireball : m_fireball)
		fireball.draw(m_spriteSheet);

	for (const Mine* mine : m_mine)
		mine->draw(m_spriteSheet);

	if (isDebugging)
		drawDebug();
}

void EntityManager::drawDebug() const
{
	for (const Player& player : m_player)
		player.drawDebug();

	for (const Bullet& bullet : m_bullet)
		bullet.drawDebug();

	for (const Fireball& fireball : m_fireball)
		fireball.drawDebug();

	for (const Mine* mine : m_mine)
		mine->drawDebug();
}

bool EntityManager::areCheckpointAvailable(int count)
{
	return std::count_if(m_spawnPoint.begin(), m_spawnPoint.end(), [](const SpawnPoint& s) { return s.m_isAvailable && !s.m_isReserved; }) >= count;
}