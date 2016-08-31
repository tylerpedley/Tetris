#include "Game.h"


Game::Game(SDLDriver* Driver) : mDriver(Driver)
{
	Grid.setDriver(Driver);
}


Game::~Game()
{
}


bool Game::init()
{
	bool success = true;
	return success;
}
