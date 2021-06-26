#include <gtest/gtest.h>

#include "../../include/Utility.h"
#include "../../include/Resolve.h"

using namespace Road;

TEST(TmpAddTest, CheckValues) {
  Road::GridLocation x{1, 4};
  Road::GridLocation y{2, 6};
  ASSERT_EQ(Heuristic::manhattan(x, y), 30);
  EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
