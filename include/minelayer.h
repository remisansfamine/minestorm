#pragma once

#include "entity.h"

class Minelayer : public Entity
{
	public:
		bool m_canSpawn = true;
		bool m_isAlive = false;

		int m_score = 1000.f;

		ConcavePolygon m_collider;

		Minelayer();

		void update(float deltaTime) override;
		void drawDebug() const;

	private:
		Vector2D m_target;

		Vector2D getTarget();

		void move(float) override;
		void rotate(float) override;
		void createCollider(float size);
};