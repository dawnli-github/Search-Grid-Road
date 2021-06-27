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

namespace Road {
class Heuristic {
 public:
  static int manhattan(GridLocation a, GridLocation b) {
    return 5 * (abs(a.x - b.x) + abs(a.y - b.y));
  }
  static int optManhattan(GridLocation a, GridLocation b) {
    int dx = abs(a.x - b.x);
    int dy = abs(a.y - b.y);
    return 5 * max(dx, dy) + 2 * min(dx, dy);
  }
};
}  // namespace Road