#pragma once

#include "referential.h"

class ParticleManager;

class Particle
{
	private:
		float m_lifeTime = 0.f;

		Vector2D m_speed;

		Referential2D m_referential;

		Color m_color;

	public:
		bool m_destroyed = false;

		Particle() = default;
		Particle(const Referential2D& referential, float lifeTime, Color color, const Vector2D& speed = Vector2D(), bool inFront = false);

		void update(float deltaTime);
		void draw() const;

		static ParticleManager* particleManager;
};