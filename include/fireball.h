#pragma once

#include "projectile.h"

#include "maths_toolbox.h"

class Fireball : public Projectile
{
	private:
		void checkCollisionPlayer();
		void checkCollisionScreenBorder();

	public:
		int m_score = 110;

		Fireball(const Referential2D& referential, Color color);

		void update(float deltaTime) override;
};