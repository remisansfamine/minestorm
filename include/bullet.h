#pragma once

#include "projectile.h"

#include "maths_toolbox.h"

class Player;

class Bullet : public Projectile
{
	private:
		Player* m_owner = nullptr;

		void checkCollisionMinelayer();
		void checkCollisionMine();
		void checkCollisionFireball();

	public:
		Bullet(const Referential2D& referential, Color color, Player* owner);

		void update(float deltaTime) override;
};