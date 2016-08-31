#ifndef SDL_DRIVER_INCLUDED
#define SDL_DRIVER_INCLUDED

#include <SDL.h>
#include <iostream>

class SDLDriver
{
public:
	SDLDriver();
	~SDLDriver();

	/* Variables */

	//Screen dimension constants
	const int WINDOW_WIDTH = 300;
	const int WINDOW_HEIGHT = 400;

	SDL_Window* window = nullptr;
	SDL_Surface* windowSurface = nullptr;
	SDL_Renderer* Renderer = nullptr;

	/* Functions */
	bool init();
	void close();
};

#endif