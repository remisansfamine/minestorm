#pragma once

#include "entity.h"

#include "input.h"

class Player : public Entity
{
	private:
		float m_fireRate = 0.3f;
		float m_shootCooldown;
		float m_friction = 0.6f;
		float m_maxSpeed = 250.f;
		float m_mass = 50.f;
		float m_kDrift = 0.5f;

		Input m_input;

		void createCollider(float size = 1.f);
		void move(float) override;
		void rotate(float) override;
		void randomTeleport();
		void checkCollision();
		void shoot();

	public:
		int m_score = 0;
		int m_life = 3;
		int m_index = 0;

		ConcavePolygon m_collider;

		Player(int index, const Input& inputs,
			   const Referential2D& referential, Color color);

		void update(float) override;
		void drawDebug() const override;
		void hurt();
};