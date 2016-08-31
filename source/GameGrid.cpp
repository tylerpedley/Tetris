#include "GameGrid.h"

GameGrid::GameGrid()
{
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 15; x++)
		{
			GridState[x][y] = false;
			Grid[x][y].h = SquareSize;
			Grid[x][y].w = SquareSize;
			Grid[x][y].x = SquareSize * x;
			Grid[x][y].y = SquareSize * y;
		}
	}

	srand(time(NULL));
}


GameGrid::~GameGrid()
{

}

void GameGrid::setDriver(SDLDriver* Driver)
{
	mDriver = Driver;
}

bool GameGrid::getGridSquareValue(int x, int y)
{
	return GridState[x][y];
}

bool GameGrid::spawnShape()
{
	if (GridState[defualt_xSpawn][defualt_ySpawn] == true ||
		GridState[defualt_xSpawn + 1][defualt_ySpawn] == true || 
		GridState[defualt_xSpawn + 2][defualt_ySpawn] == true || 
		GridState[defualt_xSpawn + 3][defualt_ySpawn] == true)
	{
		// Game Over
		printf("Game Over\n");
	}
	else
	{
		srand(time(NULL));
		int randNum = 1;
		//int randNum = (rand() % 7) + 1;
		shapeID = randNum;

		switch (shapeID)
		{
		case 1:
			spawnShape_I();
			break;
		case 2:
			spawnShape_J();
			break;
		case 3:
			spawnShape_L();
			break;
		case 4:
			spawnShape_O();
			break;
		case 5:
			spawnShape_S();
			break;
		case 6:
			spawnShape_T();
			break;
		case 7:
			spawnShape_Z();
			break;
		}
	}
	return true;
}

void GameGrid::redrawShape()
{
	SDL_SetRenderDrawColor(mDriver->Renderer, r, g, b, a);
	SDL_RenderFillRect(mDriver->Renderer, &Grid[blockOne_xPos][blockOne_yPos]);
	SDL_RenderFillRect(mDriver->Renderer, &Grid[blockTwo_xPos][blockTwo_yPos]);
	SDL_RenderFillRect(mDriver->Renderer, &Grid[blockThree_xPos][blockThree_yPos]);
	SDL_RenderFillRect(mDriver->Renderer, &Grid[blockFour_xPos][blockFour_yPos]);
	SDL_RenderPresent(mDriver->Renderer);
}

void GameGrid::moveShape(Direction Dir)
{
	bool newShapeNeeded = false;

	switch (Dir)
	{
	case DOWN:
		if (isShapeOnBottom())
		{
			newShapeNeeded = true;
		}
		else if (canMoveDown())
		{
			// Make the space black again
			eraseShape();

			// Now move the shape down one space
			blockOne_yPos++;
			blockTwo_yPos++;
			blockThree_yPos++;
			blockFour_yPos++;

			// Set state of new shape pos to true (in use)
			GridState[blockOne_xPos][blockOne_yPos] = true;
			GridState[blockTwo_xPos][blockTwo_yPos] = true;
			GridState[blockThree_xPos][blockThree_yPos] = true;
			GridState[blockFour_xPos][blockFour_yPos] = true;

			// Draw the shape in its new pos
			redrawShape();
		}
		else
		{
			newShapeNeeded = true;
		}
		break;
	case LEFT:
		if (canMoveLeft() && isShapeOnLeftBorder() == false)
		{
			// Shape has moved out this position, state is empty
			GridState[blockOne_xPos][blockOne_yPos] = false;
			GridState[blockTwo_xPos][blockTwo_yPos] = false;
			GridState[blockThree_xPos][blockThree_yPos] = false;
			GridState[blockFour_xPos][blockFour_yPos] = false;

			// Make the space black again
			eraseShape();

			// Now move the shape to the left one space
			blockOne_xPos--;
			blockTwo_xPos--;
			blockThree_xPos--;
			blockFour_xPos--;

			// Set state of new shape pos to true (in use)
			GridState[blockOne_xPos][blockOne_yPos] = true;
			GridState[blockTwo_xPos][blockTwo_yPos] = true;
			GridState[blockThree_xPos][blockThree_yPos] = true;
			GridState[blockFour_xPos][blockFour_yPos] = true;

			// Draw the shape in its new pos
			redrawShape();
		}

		break;

	case RIGHT:
		if (canMoveRight() && isShapeOnRightBorder() == false)
		{
			// Shape has moved out this position, state is empty
			GridState[blockOne_xPos][blockOne_yPos] = false;
			GridState[blockTwo_xPos][blockTwo_yPos] = false;
			GridState[blockThree_xPos][blockThree_yPos] = false;
			GridState[blockFour_xPos][blockFour_yPos] = false;

			// Make the space black again
			eraseShape();

			// Now move the shape right one space
			blockOne_xPos++;
			blockTwo_xPos++;
			blockThree_xPos++;
			blockFour_xPos++;

			// Set state of new shape pos to true (in use)
			GridState[blockOne_xPos][blockOne_yPos] = true;
			GridState[blockTwo_xPos][blockTwo_yPos] = true;
			GridState[blockThree_xPos][blockThree_yPos] = true;
			GridState[blockFour_xPos][blockFour_yPos] = true;

			// Draw the shape in its new pos
			redrawShape();
		}
		break;
	}
	if (newShapeNeeded)
	{
		spawnShape();
		newShapeNeeded = false;
	}

	//system("CLS");
	//drawStates();
}

void GameGrid::eraseShape()
{
	GridState[blockOne_xPos][blockOne_yPos] = false;
	GridState[blockTwo_xPos][blockTwo_yPos] = false;
	GridState[blockThree_xPos][blockThree_yPos] = false;
	GridState[blockFour_xPos][blockFour_yPos] = false;

	SDL_SetRenderDrawColor(mDriver->Renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderFillRect(mDriver->Renderer, &Grid[blockOne_xPos][blockOne_yPos]);
	SDL_RenderFillRect(mDriver->Renderer, &Grid[blockTwo_xPos][blockTwo_yPos]);
	SDL_RenderFillRect(mDriver->Renderer, &Grid[blockThree_xPos][blockThree_yPos]);
	SDL_RenderFillRect(mDriver->Renderer, &Grid[blockFour_xPos][blockFour_yPos]);
	SDL_RenderPresent(mDriver->Renderer);
}

void GameGrid::RotateShape()
{
	int old_blockOne_xPos = blockOne_xPos;
	int old_blockTwo_xPos = blockTwo_xPos;
	int old_blockThree_xPos = blockThree_xPos;
	int old_blockFour_xPos = blockFour_xPos;
	int old_blockOne_yPos = blockOne_yPos;
	int old_blockTwo_yPos = blockTwo_yPos;
	int old_blockThree_yPos = blockThree_yPos;
	int old_blockFour_yPos = blockFour_yPos;

	switch (Rotation)
	{
	case NONE:
		
		eraseShape();

		// Change shapes block pos's
		blockOne_xPos += 1;
		blockTwo_yPos += 1;
		blockThree_xPos -= 1;
		blockThree_yPos += 2;
		blockFour_xPos -= 2;
		blockFour_yPos += 3;

		if (RotationValid())
		{
			// Area is clear
			printf("Rotation Valid\n");

			// Set area to "in use"
			GridState[blockOne_xPos][blockOne_yPos] = true;
			GridState[blockTwo_xPos][blockTwo_yPos] = true;
			GridState[blockThree_xPos][blockThree_yPos] = true;
			GridState[blockFour_xPos][blockFour_yPos] = true;

			redrawShape();
		}
		else
		{
			printf("Rotation invalid[N]\n");

			GridState[old_blockOne_xPos][old_blockOne_yPos] = true;
			GridState[old_blockTwo_xPos][old_blockTwo_yPos] = true;
			GridState[old_blockThree_xPos][old_blockThree_yPos] = true;
			GridState[old_blockFour_xPos][old_blockFour_yPos] = true;

			redrawShape();
		}
		Rotation = QUATER;
		break;
	case QUATER:

		eraseShape();

		// Change shapes block pos's
		blockOne_xPos -= 1;
		blockTwo_yPos -= 1;
		blockThree_xPos += 1;
		blockThree_yPos -= 2;
		blockFour_xPos += 2;
		blockFour_yPos -= 3;

		if (RotationValid())
		{
			// Area is clear
			printf("Rotation Valid\n");

			// Set area to "in use"
			GridState[blockOne_xPos][blockOne_yPos] = true;
			GridState[blockTwo_xPos][blockTwo_yPos] = true;
			GridState[blockThree_xPos][blockThree_yPos] = true;
			GridState[blockFour_xPos][blockFour_yPos] = true;

			redrawShape();
		}
		else
		{
			printf("Rotation invalid[N]\n");

			GridState[old_blockOne_xPos][old_blockOne_yPos] = true;
			GridState[old_blockTwo_xPos][old_blockTwo_yPos] = true;
			GridState[old_blockThree_xPos][old_blockThree_yPos] = true;
			GridState[old_blockFour_xPos][old_blockFour_yPos] = true;

			redrawShape();
		}
		Rotation = HALF;
		break;
	case HALF:

		eraseShape();

		// Change shapes block pos's
		blockOne_xPos += 1;
		blockTwo_yPos += 1;
		blockThree_xPos -= 1;
		blockThree_yPos += 2;
		blockFour_xPos -= 2;
		blockFour_yPos += 3;

		if (RotationValid())
		{
			// Area is clear
			printf("Rotation Valid\n");

			// Set area to "in use"
			GridState[blockOne_xPos][blockOne_yPos] = true;
			GridState[blockTwo_xPos][blockTwo_yPos] = true;
			GridState[blockThree_xPos][blockThree_yPos] = true;
			GridState[blockFour_xPos][blockFour_yPos] = true;

			redrawShape();
		}
		else
		{
			printf("Rotation invalid[N]\n");

			GridState[old_blockOne_xPos][old_blockOne_yPos] = true;
			GridState[old_blockTwo_xPos][old_blockTwo_yPos] = true;
			GridState[old_blockThree_xPos][old_blockThree_yPos] = true;
			GridState[old_blockFour_xPos][old_blockFour_yPos] = true;

			redrawShape();
		}
		Rotation = THREE_QUATERS;
		break;
	case THREE_QUATERS:

		eraseShape();

		// Change shapes block pos's
		blockOne_xPos -= 3;
		blockTwo_xPos -= 2;
		blockThree_xPos -= 1;
		blockFour_xPos;

		if (RotationValid())
		{
			// Area is clear
			printf("Rotation Valid\n");

			// Set area to "in use"
			GridState[blockOne_xPos][blockOne_yPos] = true;
			GridState[blockTwo_xPos][blockTwo_yPos] = true;
			GridState[blockThree_xPos][blockThree_yPos] = true;
			GridState[blockFour_xPos][blockFour_yPos] = true;

			redrawShape();
		}
		else
		{
			printf("Rotation invalid[N]\n");

			GridState[old_blockOne_xPos][old_blockOne_yPos] = true;
			GridState[old_blockTwo_xPos][old_blockTwo_yPos] = true;
			GridState[old_blockThree_xPos][old_blockThree_yPos] = true;
			GridState[old_blockFour_xPos][old_blockFour_yPos] = true;

			redrawShape();
		}
		Rotation = NONE;
		break;
	}
}

bool GameGrid::RotationValid()
{
	switch (Rotation)
	{
	case NONE:
		switch (shapeID)
		{
		case 1:			
			// Check if area the shape is rotating into is clear
			if (GridState[blockOne_xPos]   [blockOne_yPos] == false &&
				GridState[blockTwo_xPos]   [blockTwo_yPos] == false &&
				GridState[blockThree_xPos] [blockThree_yPos] == false &&
				GridState[blockFour_xPos]  [blockFour_yPos] == false)
			{
				return true;
			}
		
			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;

		case 7:

			break;
		}

		break;
	case QUATER:
		switch (shapeID)
		{
		case 1:
			// Check if area the shape is rotating into is clear
			if (GridState[blockOne_xPos][blockOne_yPos] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos] == false &&
				GridState[blockThree_xPos][blockThree_yPos] == false &&
				GridState[blockFour_xPos][blockFour_yPos] == false)
			{
				return true;
			}

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;

		case 7:

			break;
		}
		break;
	case HALF:
		switch (shapeID)
		{
		case 1:
			// Check if area the shape is rotating into is clear
			if (GridState[blockOne_xPos][blockOne_yPos] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos] == false &&
				GridState[blockThree_xPos][blockThree_yPos] == false &&
				GridState[blockFour_xPos][blockFour_yPos] == false)
			{
				return true;
			}

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;

		case 7:

			break;
		}
		break;
	case THREE_QUATERS:
		switch (shapeID)
		{
		case 1:
			eraseShape();

			if (GridState[blockOne_xPos][blockOne_yPos] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos] == false &&
				GridState[blockThree_xPos][blockThree_yPos] == false &&
				GridState[blockFour_xPos][blockFour_yPos] == false)
			{
				return true;
			}

			break;

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;

		case 7:

			break;
		}
		break;
	}
	return false;
}

bool GameGrid::canMoveDown()
{
	switch (Rotation)
	{
	case NONE:
		if (isShapeOnBottom())
		{
			return false;
		}

		switch (shapeID) // Do the check for the shape
		{
		case 1:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 2:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 2] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 3:
			if (GridState[blockOne_xPos][blockOne_yPos + 2] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 4:
			if (GridState[blockOne_xPos][blockOne_yPos + 2] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 2] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 5:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 2] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 6:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 2] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 7:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 2] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		}
		return false;
	case QUATER:
		if (isShapeOnBottom())
		{
			return false;
		}

		switch (shapeID) // Do the check for the shape
		{
		case 1:
			if (GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 2:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 2] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 3:
			if (GridState[blockOne_xPos][blockOne_yPos + 2] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 4:
			if (GridState[blockOne_xPos][blockOne_yPos + 2] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 2] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 5:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 2] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 6:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 2] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 7:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 2] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		}
		return false;
	case HALF:
		if (isShapeOnBottom())
		{
			return false;
		}

		switch (shapeID) // Do the check for the shape
		{
		case 1:
			if (GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 2:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 2] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 3:
			if (GridState[blockOne_xPos][blockOne_yPos + 2] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 4:
			if (GridState[blockOne_xPos][blockOne_yPos + 2] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 2] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 5:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 2] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 6:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 2] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 7:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 2] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		}
		return false;
	case THREE_QUATERS:
		if (isShapeOnBottom())
		{
			return false;
		}

		switch (shapeID) // Do the check for the shape
		{
		case 1:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 2:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 2] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 3:
			if (GridState[blockOne_xPos][blockOne_yPos + 2] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 4:
			if (GridState[blockOne_xPos][blockOne_yPos + 2] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 2] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 5:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 1] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 2] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 6:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 2] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		case 7:
			if (GridState[blockOne_xPos][blockOne_yPos + 1] == false &&
				GridState[blockTwo_xPos][blockTwo_yPos + 2] == false &&
				GridState[blockThree_xPos][blockThree_yPos + 1] == false &&
				GridState[blockFour_xPos][blockFour_yPos + 1] == false)
			{
				return true;
			}
		}
		return false;
	}
}

bool GameGrid::canMoveLeft()
{
	switch (shapeID) // Do the correct check for the shape
	{
	case 1:
		if (GridState[blockOne_xPos - 1][blockOne_yPos] == false)
		{
			return true;
		}
	case 2:
		if (GridState[blockOne_xPos - 1][blockOne_yPos] == false &&
			GridState[blockTwo_xPos - 2][blockTwo_yPos] == false &&
			GridState[blockThree_xPos - 3][blockThree_yPos] == false &&
			GridState[blockFour_xPos - 1][blockFour_yPos] == false)
		{
			return true;
		}
	case 3:
		if (GridState[blockOne_xPos - 1][blockOne_yPos] == false &&
			GridState[blockFour_xPos - 1][blockFour_yPos] == false)
		{
			return true;
		}
	case 4:
		if (GridState[blockOne_xPos - 1][blockOne_yPos] == false &&
			GridState[blockThree_xPos - 1][blockThree_yPos] == false)
		{
			return true;
		}
	case 5:
		if (GridState[blockOne_xPos - 1][blockOne_yPos] == false &&
			GridState[blockThree_xPos - 1][blockThree_yPos] == false)
		{
			return true;
		}
	case 6:
		if (GridState[blockOne_xPos - 1][blockOne_yPos] == false &&
			GridState[blockFour_xPos - 1][blockFour_yPos] == false)
		{
			return true;
		}
	case 7:
		if (GridState[blockOne_xPos - 1][blockOne_yPos] == false &&
			GridState[blockThree_xPos - 1][blockThree_yPos] == false)
		{
			return true;
		}
	}
	return false;
}

bool GameGrid::canMoveRight()
{
	switch (shapeID) // Do the check for the shape
	{
	case 1:
		if (GridState[blockFour_xPos + 1][blockFour_yPos] == false)
		{
			return true;
		}
	case 2:
		if (GridState[blockThree_xPos + 1][blockThree_yPos] == false &&
			GridState[blockFour_xPos + 1][blockFour_yPos] == false)
		{
			return true;
		}
	case 3:
		if (GridState[blockThree_xPos + 1][blockThree_yPos] == false &&
			GridState[blockFour_xPos + 1][blockFour_yPos] == false)
		{
			return true;
		}
	case 4:
		if (GridState[blockTwo_xPos + 1][blockTwo_yPos] == false &&
			GridState[blockFour_xPos + 1][blockFour_yPos] == false)
		{
			return true;
		}
	case 5:
		if (
			GridState[blockTwo_xPos + 1][blockTwo_yPos] == false &&
			GridState[blockFour_xPos + 1][blockFour_yPos] == false)
		{
			return true;
		}
	case 6:
		if (GridState[blockThree_xPos + 1][blockThree_yPos] == false &&
			GridState[blockFour_xPos + 1][blockFour_yPos] == false)
		{
			return true;
		}
	case 7:
		if (GridState[blockTwo_xPos + 1][blockTwo_yPos] == false &&
			GridState[blockFour_xPos + 1][blockFour_yPos] == false)
		{
			return true;
		}
	}
	return false;
}

bool GameGrid::isShapeOnBottom()
{
	if (blockOne_yPos == 19 ||
		blockTwo_yPos == 19 ||
		blockThree_yPos == 19 ||
		blockFour_yPos == 19)
	{
		return true;
	}
	return false;
}

bool GameGrid::isShapeOnLeftBorder()
{
	if (blockOne_xPos == 0 ||
		blockTwo_xPos == 0 ||
		blockThree_xPos == 0 ||
		blockFour_xPos == 0)
	{
		return true;
	}
	return false;
}

bool GameGrid::isShapeOnRightBorder()
{
	if (blockOne_xPos == 14 ||
		blockTwo_xPos == 14 ||
		blockThree_xPos == 14 ||
		blockFour_xPos == 14)
	{
		return true;
	}
	return false;
}

void GameGrid::drawStates()
{
	for (int y = 0; y < 20; y++)
	{
		std::cout << std::endl;
		for (int x = 0; x < 15; x++)
		{
			if (GridState[x][y])
				std::cout << "0 ";
			else
				std::cout << "- ";
		}
	}
}

void GameGrid::resetDefaultSpawnValues()
{
	blockOne_xPos = defualt_xSpawn;
	blockOne_yPos = defualt_ySpawn;
	blockTwo_xPos = defualt_xSpawn;
	blockTwo_yPos = defualt_ySpawn;
	blockThree_xPos = defualt_xSpawn;
	blockThree_yPos = defualt_ySpawn;
	blockFour_xPos = defualt_xSpawn;
	blockFour_yPos = defualt_ySpawn;
}
void GameGrid::setGridState()
{
	GridState[blockOne_xPos][blockOne_yPos] = true;
	GridState[blockTwo_xPos][blockTwo_yPos] = true;
	GridState[blockThree_xPos][blockThree_yPos] = true;
	GridState[blockFour_xPos][blockFour_yPos] = true;
}
void GameGrid::spawnShape_I()
{
	r = 0xFF;
	g = 0x00;
	b = 0x00;
	a = 0xFF;

	Rotation = NONE;

	// Spawn shape at default spot
	resetDefaultSpawnValues();

	// Offset default spawn to create blocks in correct shape 
	blockOne_xPos = defualt_xSpawn - 1;
	blockOne_yPos = defualt_ySpawn;
	blockTwo_xPos = defualt_xSpawn;
	blockTwo_yPos = defualt_ySpawn;
	blockThree_xPos = defualt_xSpawn + 1;
	blockThree_yPos = defualt_ySpawn;
	blockFour_xPos = defualt_xSpawn + 2;
	blockFour_yPos = defualt_ySpawn;

	setGridState();

	redrawShape();
}

void GameGrid::spawnShape_J()
{
	r = 0xFF;
	g = 0x00;
	b = 0xFF;
	a = 0xFF;

	Rotation = NONE;

	// Spawn shape at default spot
	resetDefaultSpawnValues();

	// Offset default spawn to create blocks in correct shape 
	blockOne_xPos = defualt_xSpawn;
	blockOne_yPos = defualt_ySpawn;
	blockTwo_xPos = defualt_xSpawn + 1;
	blockTwo_yPos = defualt_ySpawn;
	blockThree_xPos = defualt_xSpawn + 2;
	blockThree_yPos = defualt_ySpawn;
	blockFour_xPos = defualt_xSpawn + 2;
	blockFour_yPos = defualt_ySpawn + 1;

	setGridState();

	redrawShape();
}

void GameGrid::spawnShape_L()
{
	r = 0xFF;
	g = 0xFF;
	b = 0x00;
	a = 0xFF;

	Rotation = NONE;

	// Spawn shape at default spot
	resetDefaultSpawnValues();

	// Offset default spawn to create blocks in correct shape 
	blockOne_xPos = defualt_xSpawn;
	blockOne_yPos = defualt_ySpawn;
	blockTwo_xPos = defualt_xSpawn + 1;
	blockTwo_yPos = defualt_ySpawn;
	blockThree_xPos = defualt_xSpawn + 2;
	blockThree_yPos = defualt_ySpawn;
	blockFour_xPos = defualt_xSpawn;
	blockFour_yPos = defualt_ySpawn + 1;

	setGridState();

	redrawShape();
}

void GameGrid::spawnShape_O()
{
	r = 0x00;
	g = 0xFF;
	b = 0xFF;
	a = 0xFF;

	Rotation = NONE;

	// Spawn shape at default spot
	resetDefaultSpawnValues();

	// Offset default spawn to create blocks in correct shape 
	blockOne_xPos = defualt_xSpawn;
	blockOne_yPos = defualt_ySpawn;
	blockTwo_xPos = defualt_xSpawn + 1;
	blockTwo_yPos = defualt_ySpawn;
	blockThree_xPos = defualt_xSpawn;
	blockThree_yPos = defualt_ySpawn + 1;
	blockFour_xPos = defualt_xSpawn + 1;
	blockFour_yPos = defualt_ySpawn + 1;

	setGridState();

	redrawShape();
}

void GameGrid::spawnShape_S()
{
	r = 0x00;
	g = 0x00;
	b = 0xFF;
	a = 0xFF;

	Rotation = NONE;

	// Spawn shape at default spot
	resetDefaultSpawnValues();

	// Offset default spawn to create blocks in correct shape 
	blockOne_xPos = defualt_xSpawn;
	blockOne_yPos = defualt_ySpawn + 1;
	blockTwo_xPos = defualt_xSpawn + 1;
	blockTwo_yPos = defualt_ySpawn + 1;
	blockThree_xPos = defualt_xSpawn + 1;
	blockThree_yPos = defualt_ySpawn;
	blockFour_xPos = defualt_xSpawn + 2;
	blockFour_yPos = defualt_ySpawn;

	setGridState();

	redrawShape();
}

void GameGrid::spawnShape_T()
{
	r = 0xD3;
	g = 0xD3;
	b = 0xD3;
	a = 0xFF;

	Rotation = NONE;

	// Spawn shape at default spot
	resetDefaultSpawnValues();

	// Offset default spawn to create blocks in correct shape 
	blockOne_xPos = defualt_xSpawn;
	blockOne_yPos = defualt_ySpawn;
	blockTwo_xPos = defualt_xSpawn + 1;
	blockTwo_yPos = defualt_ySpawn;
	blockThree_xPos = defualt_xSpawn + 2;
	blockThree_yPos = defualt_ySpawn;
	blockFour_xPos = defualt_xSpawn + 1;
	blockFour_yPos = defualt_ySpawn + 1;

	setGridState();

	redrawShape();
}

void GameGrid::spawnShape_Z()
{
	r = 0x32;
	g = 0xCD;
	b = 0x32;
	a = 0xFF;

	Rotation = NONE;

	// Spawn shape at default spot
	resetDefaultSpawnValues();

	// Offset default spawn to create blocks in correct shape 
	blockOne_xPos = defualt_xSpawn;
	blockOne_yPos = defualt_ySpawn;
	blockTwo_xPos = defualt_xSpawn + 1;
	blockTwo_yPos = defualt_ySpawn;
	blockThree_xPos = defualt_xSpawn + 1;
	blockThree_yPos = defualt_ySpawn + 1;
	blockFour_xPos = defualt_xSpawn + 2;
	blockFour_yPos = defualt_ySpawn + 1;

	setGridState();

	redrawShape();
}