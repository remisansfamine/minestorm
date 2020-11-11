#include "entity_manager.h"

#include "floating_mine.h"
#include "fireball_mine.h"
#include "magnetic_mine.h"
#include "magnetic_fireball_mine.h"

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

		Player(i, input[i], Vector2D(x, y), Vector2D(1.f, 0.f));
	}

	new FloatingMine(Vector2D(320.f, 400.f), Vector2D(1.f, 0.f));
}

EntityManager::~EntityManager()
{
	UnloadTexture(m_spriteSheet);

	for (Mine* mine : m_mine)
		delete mine;
}

void EntityManager::update(float deltaTime)
{
	for (Player& player : m_player)
		player.update(deltaTime);

	for (Projectile& bullet : m_bullet)
		bullet.update(deltaTime);

	for (Mine* mine : m_mine)
		mine->update(deltaTime);
}

void EntityManager::draw(bool isDebugging)
{
	for (Player& player : m_player)
		player.draw(m_spriteSheet);

	for (Projectile& bullet : m_bullet)
		bullet.draw(m_spriteSheet);

	for (Mine* mine : m_mine)
		mine->draw(m_spriteSheet);

	if (isDebugging)
		drawDebug();
}

void EntityManager::drawDebug()
{
	for (Player& player : m_player)
		player.drawDebug();

	for (Projectile& bullet : m_bullet)
		bullet.drawDebug();

	for (Mine* mine : m_mine)
		mine->drawDebug();
}