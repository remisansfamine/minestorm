#include "particle_manager.h"

#include <algorithm>

#include <iostream>

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
		// Check if an inactive particle exists in the front particles list
		// If it exists, save the new particle in it 
		for (Particle& p : m_frontParticles)
		{
			if (p.m_destroyed)
			{
				p = particle;
				return;
			}
		}
		m_frontParticles.push_back(particle);

		return;
	}

	for (Particle& p : m_backParticles)
	{
		// Check if an inactive particle exists in the back particles list
		// If it exists, save the new particle in it 
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