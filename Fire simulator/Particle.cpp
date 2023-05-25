#include "Particle.h"
Particle::Particle()
{
	//m_x = (2.0f * static_cast<float>(rand()) / RAND_MAX) - 1.0f;
	//m_y = (2.0f * static_cast<float>(rand()) / RAND_MAX) - 1.0f;
	m_x = 0;
	m_y = 0;
	m_dir = (2.0f * M_PI*static_cast<float>(rand()) / RAND_MAX);
	m_speed = 0.0001f * ((2.0f * (rand()) / RAND_MAX) - 1.0f);
}

void Particle::Update(const unsigned long long& time)
{
	float xSpeed = time*m_speed * sin(m_dir);
	float ySpeed = time*m_speed * cos(m_dir);
	m_x += xSpeed;
	m_y += ySpeed;
}