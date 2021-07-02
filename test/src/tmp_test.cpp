#include <gtest/gtest.h>

#include "../../include/Resolve.h"
#include "../../include/Utility.h"

using namespace road;

TEST(AStarHeuristicTest, CheckManhatten) {
  GridLocation x{1, 4};
  GridLocation y{2, 6};
  ASSERT_EQ(Heuristic::manhattan(x, y), 15);
  EXPECT_TRUE(true);
}

TEST(AStarHeuristicTest, CheckOptManhatten) {
  GridLocation x{2, 7};
  GridLocation y{4, 10};
  ASSERT_EQ(Heuristic::optManhattan(x, y), 19);
  EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
