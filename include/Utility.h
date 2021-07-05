/**
 * @file Utility.h
 * @author Dawn Li (dawnli619215645@gmail.com)
 * @brief Util
 * @version 0.1
 * @date 2021-06-25
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include "Graph.h"

using namespace std;

namespace road {
class Heuristic {
 public:
  static double manhattan(GridLocation a, GridLocation b) {
    return (abs(a.x - b.x) + abs(a.y - b.y));
  }
  static double optManhattan(GridLocation a, GridLocation b) {
    int dx = abs(a.x - b.x);
    int dy = abs(a.y - b.y);
    return (2 - sqrt(2)) * max(dx, dy) + (sqrt(2) - 1) * (dx + dy);
  }

 private:
};
}  // namespace road
