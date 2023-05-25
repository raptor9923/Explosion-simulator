#pragma once
#include"SDL.h"
#include"Window.h"
#include"graphics.h"
#include<stdlib.h>
#include<time.h>



int main (int argc, char* argv[])
{
	srand(time(nullptr));
	const int width{ 800 };
	const int height { 800 };
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return -1;
	Window window;
	window.Initialize("simulation",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,width,height);
	Graphics graphics;
	graphics.Initialize(window.GetWindow(), width,height);
	while (window.ProcessEvents())
	{
		graphics.Update();
	}
	SDL_Quit();
}