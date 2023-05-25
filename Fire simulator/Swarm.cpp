#include "Swarm.h"

Swarm::Swarm()
{
	m_particles.resize(PARTICLES_NUMBER);
}

Particle* Swarm::GetParticles()
{
	return m_particles.data();
}
std::vector<Particle>& Swarm::GetVector()
{
	return m_particles;
}
