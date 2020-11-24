#pragma once

#include "entity.h"

class SpawnPoint;

class Mine : public Entity
{
	protected:
		int m_mineSize = 2;

		void move(float) override;
		void rotate(float) override;
		virtual void createCollider(float size = 1.f) = 0;

	public:
		int m_score = 0.f;

		ConcavePolygon m_collider;

		Mine(int size, SpawnPoint* sp = nullptr);
		~Mine();

		void update(float deltaTime) override;
		void drawDebug() const override;
		virtual void atDestroy() = 0;
};