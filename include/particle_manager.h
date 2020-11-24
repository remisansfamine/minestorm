#pragma once

#include "particle.h"

#include <vector>

class ParticleManager
{
	private:
		void clear();

	public:
		std::vector<Particle> m_frontParticles;
		std::vector<Particle> m_backParticles;

		ParticleManager();
		~ParticleManager();

		void update(float deltaTime);

		// Draw entities, then draw particles
		void drawFront() const;

		// Draw particles, then draw entities
		void drawBack() const;

		void addParticle(const Particle& particle, bool isInFront = false);

		void reset();
};