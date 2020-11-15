#pragma once

#include "entity.h"

#include "entity_manager.h"

class Projectile : public Entity
{
	public:
		Projectile(const Referential2D& referential, Color color);
		void update(float deltaTime) override;
		void drawDebug() const override;
		Circle getCircle() const;

	private:
		float m_radius = 13.f;
		void rotate(float deltaTime) override;
		void move(float deltaTime) override;
};