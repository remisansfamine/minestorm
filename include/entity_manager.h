#pragma once

#include <vector>

#include "player.h"

class Mine;
class Projectile;

class EntityManager
{
	private:
		Texture2D m_spriteSheet;
		void drawDebug();
		void clear();

	public:
		EntityManager();
		~EntityManager();

		std::vector<Player> m_player;
		std::vector<Mine*> m_mine;
		std::vector<Projectile*> m_projectile;

		void update(float);
		void draw(bool isDebugging);
};