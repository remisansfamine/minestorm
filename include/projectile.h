#pragma once

#include "entity.h"

class Projectile : public Entity
{
	protected:
		float m_lifeTime;
		float m_radius = 13.5f;

		void rotate(float deltaTime) override;
		void move(float deltaTime) override;

		Circle m_collider;

	public:
		Projectile(const Referential2D& referential, Color color = WHITE);
		~Projectile();

		void update(float deltaTime) override;
		void drawDebug() const override;
		Circle getCircle() const;
};