#ifndef GAME_GRID_INCLUDED
#define GAME_GRID_INCLUDED

#include <iostream>
#include "SDLDriver.h"
#include <math.h>
#include <time.h>

class GameGrid
{
public:
	GameGrid();
	~GameGrid();

	enum Direction
	{
		DOWN,
		LEFT,
		RIGHT
	};
	enum ShapeRotation
	{
		NONE,
		QUATER,
		HALF,
		THREE_QUATERS,
	};
	ShapeRotation Rotation = NONE;

	bool spawnShape();
	void eraseShape();
	void setDriver(SDLDriver* Driver);
	void moveShape(Direction Dir);
	void RotateShape();

	// Spawn shapes
	void setGridState();
	void spawnShape_I();
	void spawnShape_J();
	void spawnShape_L();
	void spawnShape_O();
	void spawnShape_S();
	void spawnShape_T();
	void spawnShape_Z();

	bool canMoveDown();
	bool canMoveLeft();
	bool canMoveRight();
	bool isShapeOnBottom();
	bool isShapeOnLeftBorder();
	bool isShapeOnRightBorder();
	bool RotationValid();
	void redrawShape();
	void drawStates();
	void redrawGrid();
	void resetDefaultSpawnValues();
	bool getGridSquareValue(int x, int y);

private:
	const int SquareSize = 20;
	SDLDriver* mDriver = nullptr;

	SDL_Rect Grid[15][20];
	bool GridState[15][20];
	const int defualt_xSpawn = 6;
	const int defualt_ySpawn = 0;

	int blockOne_xPos = defualt_xSpawn;
	int blockOne_yPos = defualt_ySpawn;
	int blockTwo_xPos = defualt_xSpawn;
	int blockTwo_yPos = defualt_ySpawn;
	int blockThree_xPos = defualt_xSpawn;
	int blockThree_yPos = defualt_ySpawn;
	int blockFour_xPos = defualt_xSpawn;
	int blockFour_yPos = defualt_ySpawn;

	int r;
	int g;
	int b;
	int a;

	int shapeID;
};

#endif