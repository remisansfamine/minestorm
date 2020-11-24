#include "particle_manager.h"

#include <algorithm>

ParticleManager::ParticleManager()
{
	Particle::particleManager = this;
}

ParticleManager::~ParticleManager()
{
	Particle::particleManager = nullptr;
	reset();
}

void ParticleManager::update(float deltaTime)
{
	for (Particle& particle : m_frontParticles)
	{
		if (!particle.m_destroyed)
			particle.update(deltaTime);
	}

	for (Particle& particle : m_backParticles)
	{
		if (!particle.m_destroyed)
			particle.update(deltaTime);
	}
}

void ParticleManager::addParticle(const Particle& particle, bool isInFront)
{
	if (isInFront)
	{
		for (Particle& p : m_frontParticles)
		{
			if (p.m_destroyed)
			{
				p = particle;
				p.m_destroyed = false;
				return;
			}
		}
		m_frontParticles.push_back(particle);

		return;
	}

	for (Particle& p : m_backParticles)
	{
		if (p.m_destroyed)
		{
			p = particle;
			return;
		}
	}
	m_backParticles.push_back(particle);
}

void ParticleManager::drawFront() const
{
	for (const Particle& particle : m_frontParticles)
	{
		if (!particle.m_destroyed)
			particle.draw();
	}
}

void ParticleManager::drawBack() const
{
	for (const Particle& particle : m_backParticles)
	{
		if (!particle.m_destroyed)
			particle.draw();
	}
}


void ParticleManager::reset()
{
	m_frontParticles.clear();
	m_backParticles.clear();
}