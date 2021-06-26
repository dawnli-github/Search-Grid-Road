/**
 * @file Graph.cpp
 * @author Dawn Li (dawnli619215645@gmail.com)
 * @brief Graph
 * @version 0.1
 * @date 2021-06-25
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "../include/Graph.h"

namespace Road {

bool operator==(GridLocation a, GridLocation b) {
  return a.x == b.x && a.y == b.y;
}

bool operator!=(GridLocation a, GridLocation b) { return !(a == b); }

bool operator<(GridLocation a, GridLocation b) {
  return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

std::basic_iostream<char>::basic_ostream& operator<<(
    std::basic_iostream<char>::basic_ostream& out, const GridLocation& loc) {
  out << '(' << loc.x << ',' << loc.y << ')';
  return out;
}
}  // namespace Road
