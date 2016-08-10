#include "..\source\Tetris.h"
#include "gtest/gtest.h"
#include <cassert>
#include <iostream>

TEST(testHiker, answer_test)
{
	EXPECT_EQ(42, answer());
}
