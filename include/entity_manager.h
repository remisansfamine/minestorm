#pragma once

#include <vector>

#include "player.h"
#include "spawn_point.h"
#include "fireball.h"
#include "bullet.h"
#include "minelayer.h"

class Mine;
class Projectile;

class EntityManager
{
	private:
		int m_wave = 0;
		int m_mineCount = 2;

		Texture2D m_spriteSheet;

		void drawDebug() const;
		void clear();
		void changeWave();

	public:
		EntityManager(int playerCount = 2);
		~EntityManager();

		Input m_input[4];

		std::vector<SpawnPoint> m_spawnPoints;
		std::vector<Player>		m_players;
		std::vector<Mine*>		m_mines;
		std::vector<Fireball>	m_fireballs;
		std::vector<Bullet>		m_bullets;

		Minelayer m_minelayer;

		void setPlayerCount(int count = 1);
		void spawnMine(SpawnPoint* sp = nullptr);
		void update(float);
		void updateEntities(float deltaTime);
		void draw(bool isDebugging) const;
		bool areCheckpointAvailable(int count = 0);
		void reset();
};