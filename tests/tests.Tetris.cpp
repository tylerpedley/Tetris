#include "..\source\GameGrid.h"
#include "gtest/gtest.h"
#include <cassert>
#include <iostream>

class TetrisTests : public ::testing::Test
{
public:
	TetrisTests() {} ;
	~TetrisTests() {} ;

	GameGrid Grid;
};
/*
TEST_F(TetrisTests, game_grid_initalizes_with_all_squares_empty)
{
	EXPECT_EQ(0, Grid.getGridSquareValue(0, 0));
	EXPECT_EQ(0, Grid.getGridSquareValue(1, 8));
	EXPECT_EQ(0, Grid.getGridSquareValue(9, 15));
}

TEST_F(TetrisTests, if_the_area_below_a_shape_is_clear_it_can_move_down)
{
	// Create shape
	Grid.spawnShape_I();

	// The grid now only contains one shape at the top and below is clear

	EXPECT_TRUE(Grid.canMoveDown());

	Grid.moveShape(GameGrid::DOWN);

	// Spawn area is empty (shape moved)
	EXPECT_FALSE(Grid.getGridSquareValue(5, 0));
	EXPECT_FALSE(Grid.getGridSquareValue(6, 0));
	EXPECT_FALSE(Grid.getGridSquareValue(7, 0));
	EXPECT_FALSE(Grid.getGridSquareValue(8, 0));

	// One space below inital spawn now contains the shape
	EXPECT_TRUE(Grid.getGridSquareValue(5, 1));
	EXPECT_TRUE(Grid.getGridSquareValue(6, 1));
	EXPECT_TRUE(Grid.getGridSquareValue(7, 1));
	EXPECT_TRUE(Grid.getGridSquareValue(8, 1));
}*/