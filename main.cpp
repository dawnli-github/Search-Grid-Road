/**
 * @file main.cpp
 * @author Dawn Li (dawnli619215645@gmail.com)
 * @brief main
 * @version 0.1
 * @date 2021-06-25
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdlib.h>

#include <ctime>

#include "include/Resolve.h"

using namespace std;

using namespace Road;
int main() {
  srand(time(0));
  const int size = 30;
  Resolve test;
  test.set_size(size, size);
  vector<GridLocation> walls;
  int count = 0;
  GridLocation start{rand() % (size / 4), rand() % (size / 4)};
  GridLocation goal{(size / 2) + rand() % (size / 2),
                    (size / 2) + rand() % (size / 2)};
  while (count <= size * 15) {
    GridLocation id{rand() % size, rand() % size};
    if (id != start && id != goal) {
      walls.emplace_back(id);
      ++count;
    }
  }
  test.set_walls(walls);
  test.set_start(start);
  test.set_goal(goal);
  test.run();
}