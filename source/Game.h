#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <SDL.h>
#include "SDLDriver.h"
#include "GameGrid.h"

class Game
{
public:
	Game(SDLDriver* Driver);
	~Game();

	bool init();

	// Class Objects
	SDLDriver* mDriver;
	GameGrid Grid;

	GameGrid::Direction moveDirection = GameGrid::DOWN;
	GameGrid::Direction Down = GameGrid::DOWN;
	GameGrid::Direction Left = GameGrid::LEFT;
	GameGrid::Direction Right = GameGrid::RIGHT;

};

#endif