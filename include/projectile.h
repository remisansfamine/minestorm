#pragma once

#include "entity.h"

class Projectile : public Entity
{
	public:
		Projectile(const Vector2D& pos, const Vector2D& dir, Color color);
		void update(float deltaTime) override;
		void drawDebug() override;

	private:
		void rotate(float deltaTime) override;
		void move(float deltaTime) override;
};