#pragma once

#include "projectile.h"

#include "math_toolbox.h"

class Fireball : public Projectile
{
	public:
		int m_score = 110;

		Fireball(const Referential2D& referential, Color color);
		void update(float deltaTime) override;
};