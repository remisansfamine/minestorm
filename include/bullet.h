#pragma once

#include "projectile.h"

#include "math_toolbox.h"

class Player;

class Bullet : public Projectile
{
	private:
		Player* m_owner = nullptr;

	public:
		Bullet(const Referential2D& referential, Color color, Player* owner);

		void update(float deltaTime) override;
};