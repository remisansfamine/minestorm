#include "particle.h"

#include "particle_manager.h"

#include <raylib.h>

ParticleManager* Particle::particleManager = nullptr;

Particle::Particle(const Referential2D& referential, float lifeTime,
				   Color color, const Vector2D& speed, bool inFront)
	: m_referential(referential), m_lifeTime(lifeTime),
	  m_color(color), m_speed(speed)
{
	// Check if the particle manager has not been destroyed
	if (particleManager)
		particleManager->addParticle(*this, inFront);
}

void Particle::update(float deltaTime)
{
	m_referential.m_origin += m_speed * deltaTime;

	// Change the particle alpha with deltaTime
	m_color.a -= deltaTime / m_lifeTime;

	if (m_color.a <= 0)
		m_destroyed = true;
}

void Particle::draw() const
{
	DrawCircle(m_referential.m_origin.x, m_referential.m_origin.y, 2.f, m_color);
}