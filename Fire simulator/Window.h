#pragma once
#include <string>
#include"SDL.h"
#include<memory>
class Window
{
	std::unique_ptr<SDL_Window,void(*)(SDL_Window*)> m_window;
	
public:
	Window();
	void Initialize(const std::string& title, int windowPosX, int windowPosY,int width, int height);
	bool ProcessEvents() const;
	SDL_Window* GetWindow();

};




