#pragma once

#include "entity.h"

class Projectile : public Entity
{
	public:
		Projectile(const Referential2D& referential, Color color = WHITE);
		void update(float deltaTime) override;
		void drawDebug() const override;
		Circle getCircle() const;

	protected:
		float m_lifeTime;
		float m_radius = 6.5f;
		void rotate(float deltaTime) override;
		void move(float deltaTime) override;
};