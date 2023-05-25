#include "Window.h"
void Window::Initialize(const std::string& title, int windowPosX, int windowPosY, int width, int height)
{
	m_window.reset(SDL_CreateWindow(title.c_str(), windowPosX, windowPosY, width, height, SDL_WINDOW_SHOWN));
}


bool Window::ProcessEvents() const
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return 0;
		}
	}
	return 1;
}

Window::Window():
	m_window(nullptr,SDL_DestroyWindow)
{
	
}

SDL_Window* Window::GetWindow()
{
	return m_window.get();
}