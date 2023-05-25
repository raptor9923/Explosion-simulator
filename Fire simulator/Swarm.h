#pragma once
#include"Particle.h"
#include<vector>
class Swarm
{
	
	std::vector<Particle> m_particles;
public:
	const static int PARTICLES_NUMBER{ 2000 };
	Swarm();
	Particle* GetParticles();
	std::vector<Particle>& GetVector();
};

