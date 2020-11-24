#pragma once

#include "entity.h"

class SpawnPoint : public Entity
{
	private:
		float	m_spawnCooldown;

		Vector2D	m_target;

		void move(float) override;
		void rotate(float) override;

	public:
		bool m_isInitial = true;
		bool m_isAvailable = false;

		SpawnPoint(Vector2D pos = Entity::screenBorder.pt, bool isInitial = true);

		void update(float deltaTime) override;
};