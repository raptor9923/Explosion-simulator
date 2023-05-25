#pragma once
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include<iostream>
#include<cmath>
struct Particle
{
	float m_x;
	float m_y;
	float m_speed;
	float m_dir;
	Particle();
	void Update(const unsigned long long& time);
};

