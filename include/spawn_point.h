#pragma once

#include "entity.h"

class SpawnPoint : public Entity
{
	private:
		Vector2D m_target;

		void move(float) override;
		void rotate(float) override;

	public:
		bool m_isAvailable = false;
		bool m_isReserved = false;

		SpawnPoint(Vector2D pos = Entity::screenBorder.pt, bool isAvailable = false);

		void update(float deltaTime) override;
};