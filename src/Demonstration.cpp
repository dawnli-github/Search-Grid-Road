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

#include <ctime>
#include <random>

#include "../include/Graph.h"
#include "../include/Resolve.h"


using namespace std;
using namespace Road;

int main() {
  const int size = 30;
  Resolve test;
  test.set_size(size, size);
  vector<GridLocation> walls;

  int count = 0;
  random_device rand_engine;
  uniform_int_distribution<int> rand_start(0, size / 4);
  uniform_int_distribution<int> rand_end(3 * size / 4, size - 1);
  uniform_int_distribution<int> rand_id(0, size - 1);
  GridLocation start{rand_start(rand_engine), rand_start(rand_engine)};
  GridLocation goal{rand_end(rand_engine), rand_end(rand_engine)};
  while (count <= size * size * 2 / 3) {
    GridLocation id{rand_id(rand_engine), rand_id(rand_engine)};
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
