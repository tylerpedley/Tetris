#include "SDLDriver.h"


SDLDriver::SDLDriver()
{
}


SDLDriver::~SDLDriver()
{
}


bool SDLDriver::init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Failed to initalize SDL, error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		windowSurface = SDL_GetWindowSurface(window);

		Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (Renderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
	}

	return success;
}

void SDLDriver::close()
{
	SDL_DestroyRenderer(Renderer);
	SDL_FreeSurface(windowSurface);
	SDL_DestroyWindow(window);

	Renderer = nullptr;
	window = nullptr;
	windowSurface = nullptr;

	SDL_Quit();
}