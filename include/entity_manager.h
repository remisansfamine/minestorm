#pragma once

#include <vector>

#include "player.h"
#include "projectile.h"

class Mine;

class EntityManager
{
	private:
		Texture2D m_spriteSheet;
		void drawDebug();

	public:
		EntityManager();
		~EntityManager();

		std::vector<Player> m_player;
		std::vector<Mine*> m_mine;
		std::vector<Projectile> m_bullet;

		void update(float);
		void draw(bool isDebugging);
};