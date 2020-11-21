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

		Texture2D m_spriteSheet;
		void drawDebug() const;
		void clear();
		void spawnMine();
		void changeWave();

	public:
		EntityManager(int playerCount = 2);
		~EntityManager();

		Input m_input[4];

		std::vector<SpawnPoint> m_spawnPoint;
		std::vector<Player>		m_player;
		std::vector<Mine*>		m_mine;
		std::vector<Fireball>	m_fireball;
		std::vector<Bullet>		m_bullet;

		Minelayer m_minelayer;

		void setPlayerCount(int count = 1);
		void update(float);
		void draw(bool isDebugging) const;
		bool areCheckpointAvailable(int count = 0);
		void reset();
};