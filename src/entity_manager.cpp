#include "entity_manager.h"

#include "projectile.h"

#include "floating_mine.h"
#include "fireball_mine.h"
#include "magnetic_mine.h"
#include "magnetic_fireball_mine.h"

#include <iostream>

EntityManager::EntityManager()
{
	Entity::m_entityManager = this;

	m_spriteSheet = LoadTexture("assets/minestorm_sprite_atlas_mine_storm.png");

	Input input[2] = {
		{ KEY_R, KEY_D, KEY_G, KEY_F, KEY_E, KEY_T },
		{ KEY_I, KEY_J, KEY_L, KEY_K, KEY_U, KEY_O }
	};

	Image screenData = GetScreenData();

	for (int i = 0; i < 2; i++)
	{
		float x = screenData.width * (0.25f + i * 0.5f);
		float y = screenData.height * 0.5f;

		Player(i, input[i], Referential2D(Vector2D(x, y), Vector2D(1.f, 0.f)));
	}

	new MagneticMine(Referential2D(Vector2D(320.f, 100.f), Vector2D(1.f, 0.f)));
	new FireballMine(Referential2D(Vector2D(320.f, 200.f), Vector2D(1.f, 0.f)));
	new FloatingMine(Referential2D(Vector2D(320.f, 300.f), Vector2D(1.f, 1.f)));
	new MagneticFireballMine(Referential2D(Vector2D(320.f, 400.f), Vector2D(1.f, -1.f)));
}

EntityManager::~EntityManager()
{
	UnloadTexture(m_spriteSheet);

	for (Mine* mine : m_mine)
		delete mine;

	for (Projectile* projectile : m_projectile)
		delete projectile;
}

void EntityManager::update(float deltaTime)
{
	for (Player& player : m_player)
		player.update(deltaTime);

	for (Projectile* projectile : m_projectile)
		projectile->update(deltaTime);

	for (Mine* mine : m_mine)
		mine->update(deltaTime);

	clear();
}

void EntityManager::clear()
{
	for (Player& player : m_player)
	{
		if (player.m_shouldBeDestroyed)
			break;
	}

	for (auto& pointer : m_projectile)
	{
		if (pointer && pointer->m_shouldBeDestroyed)
		{
			delete pointer;
			pointer = nullptr;
		}
	}
	m_projectile.erase(std::remove(m_projectile.begin(), m_projectile.end(), nullptr), m_projectile.end());

	for (auto& pointer : m_mine)
	{
		if (pointer->m_shouldBeDestroyed)
		{
			delete pointer;
			pointer = nullptr;
		}
	}
	m_mine.erase(std::remove(m_mine.begin(), m_mine.end(), nullptr), m_mine.end());
}


void EntityManager::draw(bool isDebugging)
{
	for (Player& player : m_player)
		player.draw(m_spriteSheet);

	for (Projectile* projectile : m_projectile)
		projectile->draw(m_spriteSheet);

	for (Mine* mine : m_mine)
		mine->draw(m_spriteSheet);

	if (isDebugging)
		drawDebug();
}

void EntityManager::drawDebug()
{
	for (Player& player : m_player)
		player.drawDebug();

	for (Projectile* projectile : m_projectile)
		projectile->drawDebug();

	for (Mine* mine : m_mine)
		mine->drawDebug();
}