#pragma once
#include"SDL.h"
#include <memory>
#include <vector>
#include<SDL_timer.h>
#include<math.h>
#include"Swarm.h"

class Graphics
{
	int m_width{};
	int m_height{};
	Uint32 m_color{};
	long double  m_deltaTime{0};
	long long m_lastTime{0};
	std::vector<Uint32> m_buffer1;
	std::vector<Uint32> m_buffer2;
	std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> m_renderer{ nullptr, &SDL_DestroyRenderer };
	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> m_texture{ nullptr,&SDL_DestroyTexture };
	Swarm m_swarm{};
public:
	Graphics();
	void Initialize(SDL_Window* window,int width,int height);
	void Update();
	void SetBit(int xPos, int yPos, Uint8 red, Uint8 green, Uint8 blue);
	void SetBit(int xPos, int yPos, Uint32 color);
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	Uint32 CalculateColor(Uint8 red, Uint8 green, Uint8 blue);
	void BlurParticles();
	void DrawParticles();
};


