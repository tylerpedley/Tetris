#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdint.h>
#include "Game.h"
#include "SDLDriver.h"
#include "Timer.h"

// Class Objects
SDLDriver MainSDLDriver;
Game Tetris(&MainSDLDriver);

int main(int argc, char* argv[])
{
	MainSDLDriver.init();
	Tetris.init();

	SDL_SetRenderDrawColor(MainSDLDriver.Renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(MainSDLDriver.Renderer);

	bool isRunning = true;

	Tetris.Grid.spawnShape();

	static int frameCounter = 0;

	while (isRunning)
	{
		SDL_Event E;
		while (SDL_PollEvent(&E) != 0 && isRunning == true)
		{
			if (E.type == SDL_QUIT)
			{
				isRunning = false;
			}
			else if (E.type == SDL_KEYDOWN)
			{
				if (E.key.keysym.sym == SDLK_DOWN)
				{
					Tetris.Grid.moveShape(Tetris.Grid.DOWN);
				}
				else if (E.key.keysym.sym == SDLK_LEFT)
				{
					Tetris.Grid.moveShape(Tetris.Grid.LEFT);
				}
				else if (E.key.keysym.sym == SDLK_RIGHT)
				{
					Tetris.Grid.moveShape(Tetris.Grid.RIGHT);
				}
				else if (E.key.keysym.sym == SDLK_r)
				{
					Tetris.Grid.RotateShape();
				}
			}
		}

		if (frameCounter == 4000000)
		{
			Tetris.Grid.moveShape(Tetris.Grid.DOWN);
			frameCounter = 0;
		}

		frameCounter++;
	}

	MainSDLDriver.close();

	return 0;
}
