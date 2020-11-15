#pragma once

#include "entity.h"

#include "input.h"

class Player : public Entity
{
	public:
		Player(int index, const Input& inputs, const Referential2D& referential);
		void update(float) override;
		void drawDebug() const override;
		ConcavePolygon m_collider;

	private:
		int m_life = 3;
		float m_mass = 50.f;
		float m_kDrift = 0.5f;
		Vector2D m_thrust;
		Input m_input;

		void createCollider();
		void move(float) override;
		void rotate(float) override;
		void randomTeleport();
};