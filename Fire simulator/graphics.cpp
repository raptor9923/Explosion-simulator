#include "graphics.h"
#include"Particle.h"
Graphics::Graphics() = default;
void Graphics::Initialize(SDL_Window* window, int width, int height)
{
	m_deltaTime = static_cast<long double>(SDL_GetTicks64());
	m_width = width;
	m_height = height;
	m_buffer1.assign(width * height, 0);
	m_buffer2.assign(width * height, 0);
	memset(m_buffer1.data(),0, width * height * sizeof(Uint32));
	m_renderer.reset(SDL_CreateRenderer(window, -1,SDL_RENDERER_PRESENTVSYNC));
	m_texture.reset(SDL_CreateTexture(m_renderer.get(),SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC,m_width,m_height));
}

void Graphics::Update()
{  
	static int fpsCount;
	static unsigned long long timeCount;
	//time
	auto timeElapsed = static_cast<long double>(SDL_GetTicks64());

	m_deltaTime = timeElapsed - m_lastTime;
	m_lastTime = timeElapsed;
	timeCount += m_deltaTime;
	if (timeCount >= 1000)
	{
		std::cout << fpsCount << "\n";
		fpsCount = 0;
		timeCount = 0;
	}
	// color functions
	
	SetColor(
		static_cast<Uint8>((1 + sin(timeElapsed * 0.0001)) * 127),
		static_cast<Uint8>((1 + sin(timeElapsed * 0.0002)) * 127),
		static_cast<Uint8>((1 + sin(timeElapsed * 0.0003)) * 127)
		);
	BlurParticles();
	DrawParticles();
	//render screen
	SDL_UpdateTexture(m_texture.get(), nullptr, m_buffer1.data(), m_width * sizeof(Uint32));
	SDL_RenderClear(m_renderer.get());
	SDL_RenderCopy(m_renderer.get(), m_texture.get(), nullptr, nullptr);
	SDL_RenderPresent(m_renderer.get());
	fpsCount++;
}

void Graphics::SetBit(int xPos, int yPos, Uint8 red, Uint8 green, Uint8 blue)
{
	
	m_buffer1[yPos * m_width + xPos] = CalculateColor(red, green, blue);
}
void Graphics::SetBit(int xPos, int yPos, Uint32 color)
{
	if (xPos >= m_width || xPos<0 || yPos>=m_height || yPos < 0)
		return;
	m_buffer1[yPos * m_width + xPos] = color;
}

void Graphics::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	
	m_color = CalculateColor(red, green, blue);
}

Uint32 Graphics::CalculateColor(Uint8 red, Uint8 green, Uint8 blue)
{
	Uint32 color{ 0 };
	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;
	return color;
}

void Graphics::DrawParticles()
{
	int iter=0;
	for (auto particle : m_swarm.GetVector())
	{
		m_swarm.GetParticles()[iter].Update(m_deltaTime);
		auto x = static_cast<int>((1.0f- m_swarm.GetParticles()[iter].m_x)*static_cast<float>(m_width)/2.0f);
		auto y = static_cast<int>((1.0f- m_swarm.GetParticles()[iter].m_y)* static_cast<float>(m_height)/2.0f);
		SetBit(x, y, m_color);
		iter++;
	}
}

void Graphics::BlurParticles()
{
	m_buffer1.swap(m_buffer2);
	for (int y=0;y<m_height;y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;
			for (int row = -1; row <= 1; row++)
			{
				for (int col = -1; col <= 1; col++)
				{
					int currX = x + col;
					int currY = y + row;
					if (currX >= 0 && currX < m_width && currY >= 0 && currY < m_height)
					{
						Uint32 color = m_buffer2[currY * m_width + currX];
						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}
			Uint8 red = redTotal / 9.0;
			Uint8 green = greenTotal / 9.0;
			Uint8 blue = blueTotal / 9.0;
			SetBit(x, y, red, green, blue);
		}
	}
}