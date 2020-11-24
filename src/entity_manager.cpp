#include "entity_manager.h"

#include "floating_mine.h"
#include "fireball_mine.h"
#include "magnetic_mine.h"
#include "magnetic_fireball_mine.h"

#include <algorithm>

#include "utils.h"

#include <iostream>

EntityManager::EntityManager(int playerCount)
{
	// Setting player inputs and entities texture

	Entity::entityManager = this;

	m_spriteSheet = LoadTexture("assets/minestorm_sprite_atlas_mine_storm.png");

	// Initialize player inputs
	m_input[0] = { KEY_R, KEY_D, KEY_G, KEY_F, KEY_E, KEY_T };
	m_input[1] = { KEY_I, KEY_J, KEY_L, KEY_K, KEY_U, KEY_O };
	m_input[2] = { KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_RIGHT_CONTROL, KEY_KP_0 };
	m_input[3] = { KEY_KP_8, KEY_KP_4, KEY_KP_6, KEY_KP_5, KEY_KP_7, KEY_KP_9 };
}

EntityManager::~EntityManager()
{
	// Unload textures and free memory

	UnloadTexture(m_spriteSheet);

	for (Mine* mine : m_mines)
		delete mine;
}

void EntityManager::setPlayerCount(int count)
{
	// Creating X players with an associeted color

	Color color[4] = { LIME, BLUE, PURPLE, PINK };

	// Get their position in a circle if there is more than one player
	Vector2D vect = Entity::screenBorder.pt;

	if (count > 1)
		vect.x += Entity::screenBorder.halfWidth * 0.5f;

	for (int i = 0; i < count; i++)
	{
		vect.rotateAround(Entity::screenBorder.pt, 2.f * M_PI / count);
		Player(i, m_input[i], Referential2D(vect), color[i]);
	}
}

void EntityManager::reset()
{
	m_spawnedMineCount = 0;

	// Clearing each list from its entities and resetting values

	Entity::gameDifficulty = 1.f;

	m_wave = 0;

	m_minelayer = Minelayer();
	m_bullets.clear();
	m_fireballs.clear();
	m_players.clear();
	m_spawnPoints.clear();

	for (Mine* mine : m_mines)
		delete mine;

	m_mines.clear();
}

void EntityManager::changeWave()
{
	m_spawnedMineCount = 0;

	// Increase by one the number of mine at each 4 waves
	m_mineCount = m_wave / 4 + 2;
	
	m_wave++;

	for (int i = 0; i < m_mineCount * 7; i++)
		SpawnPoint();

	// Increase game difficulty (enemies speed and size)
	Entity::gameDifficulty += 0.1f;

	m_minelayer.m_canSpawn = true;

	m_waveDisplayTime = 3.f;
}

void EntityManager::spawnMine(SpawnPoint* sp)
{
	// Get a random type of mine to spawn it by getting a random ID

	int type = rand() % 4;
	switch (type)
	{
		case 0:
			new FloatingMine(sp);
			break;

		case 1:
			new FireballMine(sp);
			break;

		case 2:
			new MagneticMine(sp);
			break;

		case 3:
			new MagneticFireballMine(sp);
			break;

		default:
			new FloatingMine(sp);
	}
}

void EntityManager::update(float deltaTime)
{
	if (m_spawnPoints.size() == 0)
	{
		if (m_mines.size() == 0)
			changeWave();
		else if (m_minelayer.m_canSpawn)
			m_minelayer.m_canSpawn = m_minelayer.m_destroyed = false;
	}

	// Check if there is enough spawnpoint to spawn a mine
	if (areCheckpointAvailable(7) && m_spawnedMineCount < m_mineCount)
	{
		m_spawnedMineCount++;
		spawnMine();
	}

	updateEntities(deltaTime);

	clear();
}

void EntityManager::updateEntities(float deltaTime)
{
	// Update each list
	for (SpawnPoint& spawnPoint : m_spawnPoints)
		spawnPoint.update(deltaTime);

	for (Bullet& bullet : m_bullets)
		bullet.update(deltaTime);

	for (Fireball& fireball : m_fireballs)
		fireball.update(deltaTime);

	for (Player& player : m_players)
	{
		if (!player.m_destroyed)
			player.update(deltaTime);
	}

	for (Mine* mine : m_mines)
	{
		if (mine && !mine->m_destroyed)
			mine->update(deltaTime);
	}

	if (!m_minelayer.m_destroyed)
		m_minelayer.update(deltaTime);

	m_waveDisplayTime -= deltaTime;
}

void EntityManager::clear()
{
	// Clear each list from destroyed entities

	m_spawnPoints.erase(std::remove_if(m_spawnPoints.begin(),
		m_spawnPoints.end(),
		[](const SpawnPoint& x) { return x.m_destroyed; }),
		m_spawnPoints.end());

	m_bullets.erase(std::remove_if(m_bullets.begin(),
		m_bullets.end(),
		[](const Bullet& x) { return x.m_destroyed; }),
		m_bullets.end());

	m_fireballs.erase(std::remove_if(m_fireballs.begin(),
		m_fireballs.end(),
		[](const Fireball& x) { return x.m_destroyed; }),
		m_fireballs.end());

	for (auto& minePtr : m_mines)
	{
		if (minePtr->m_destroyed)
		{
			delete minePtr;
			minePtr = nullptr;
		}
	}
	m_mines.erase(std::remove(m_mines.begin(), m_mines.end(), nullptr), m_mines.end());
}

void EntityManager::draw(bool isDebugging) const
{
	// Draw each entity individually

	for (const SpawnPoint& spawnPoint : m_spawnPoints)
		spawnPoint.draw(m_spriteSheet);

	for (const Player& player : m_players)
	{
		if (!player.m_destroyed)
			player.draw(m_spriteSheet);
	}

	for (const Bullet& bullet : m_bullets)
		bullet.draw(m_spriteSheet);

	for (const Mine* mine : m_mines)
		mine->draw(m_spriteSheet);

	if (!m_minelayer.m_destroyed)
		m_minelayer.draw(m_spriteSheet);

	for (const Fireball& fireball : m_fireballs)
		fireball.draw(m_spriteSheet);

	if (isDebugging)
		drawDebug();

	if (m_waveDisplayTime >= 0.f)
		displayWave();
}

void EntityManager::displayWave() const
{
	std::string waveString = stringConcatenateInt("Wave ", m_wave);
	DrawAlignedText(waveString.c_str(), -0.40f, Entity::screenBorder.halfWidth, Entity::screenBorder.halfWidth, 20.f, RED);
}

void EntityManager::drawDebug() const
{
	// Draw gizmos for each entity

	for (const Player& player : m_players)
	{
		if (!player.m_destroyed)
			player.drawDebug();
	}

	for (const Bullet& bullet : m_bullets)
		bullet.drawDebug();

	for (const Fireball& fireball : m_fireballs)
		fireball.drawDebug();

	for (const Mine* mine : m_mines)
		mine->drawDebug();

	if (!m_minelayer.m_destroyed)
		m_minelayer.drawDebug();
}

bool EntityManager::areCheckpointAvailable(int count)
{
	return std::count_if(m_spawnPoints.begin(),
						 m_spawnPoints.end(),
						 [](const SpawnPoint& s)
						 { return s.m_isAvailable && s.m_isInitial; })
						 > count;
}