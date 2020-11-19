#pragma once

#include "entity.h"

class SpawnPoint : public Entity
{
	private:
		void move(float) override;
		void rotate(float) override;
		Vector2D m_target;

	public:
		bool m_isAvailable = false;
		bool m_isReserved = false;

		SpawnPoint();
		void update(float deltaTime) override;
};