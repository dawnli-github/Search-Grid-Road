/**
 * @file Graph.h
 * @author Dawn Li (dawnli619215645@gmail.com)
 * @brief Graph
 * @version 0.1
 * @date 2021-06-24
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

namespace Road {

struct GridLocation {
  int x = 0;
  int y = 0;
};
bool operator==(GridLocation a, GridLocation b);
bool operator!=(GridLocation a, GridLocation b);
bool operator<(GridLocation a, GridLocation b);
std::basic_iostream<char>::basic_ostream& operator<<(
    std::basic_iostream<char>::basic_ostream& out, const GridLocation& loc);
}  // namespace Road

namespace std {
/* implement hash function so we can put GridLocation into an unordered_set */
template <>
struct hash<Road::GridLocation> {
  using argument_type = Road::GridLocation;
  using result_type = size_t;
  size_t operator()(const Road::GridLocation& id) const noexcept {
    return hash<unsigned int>()(
        static_cast<unsigned int>(id.x) ^
        (static_cast<unsigned int>(id.y) << static_cast<unsigned int>(4)));
  }
};
}  // namespace std

namespace Road {
class Graph {
 public:
  // Init
  void init(const int width, const int height) {
    _width = width;
    _height = height;
  }
  // Set
  void set_wall(const GridLocation wall) { _walls.insert(wall); }
  // Get
  int get_width() const { return _width; }
  int get_height() const { return _height; }
  unordered_set<GridLocation> get_walls() const { return _walls; }
  vector<GridLocation> get_neighbors(GridLocation current) const {
    vector<GridLocation> neighbors;
    for (auto type : _move_type) {
      GridLocation id{current.x + type.first, current.y + type.second};
      if (in_bounds(id) && passable(id)) {
        neighbors.emplace_back(id);
      }
    }
    if ((current.x + current.y) % 2 == 0) {
      reverse(neighbors.begin(), neighbors.end());
    }
    return neighbors;
  };
  // Function
  static int cost(GridLocation current, GridLocation next) {
    return abs(next.x - current.x) + abs(next.y - current.y) == 2
               ? OBLIQQUE_UNIT
               : LINEAR_UNIT;
  };

 private:
  // Check
  bool in_bounds(GridLocation id) const {
    return 0 <= id.x && id.x < _width && 0 <= id.y && id.y < _height;
  }
  bool passable(GridLocation id) const {
    return _walls.find(id) == _walls.end();
  }
  // The ratio of unit distance of the diagonal to unit distance of the straight
  // line is 1.414 : 1 ≈ 1.4 : 1 = 7 ： 5, so we use the approximate proportion
  // of integral type to speed up the operation
  static constexpr int LINEAR_UNIT = 5;
  static constexpr int OBLIQQUE_UNIT = 7;
  int _width = 0;
  int _height = 0;
  unordered_set<GridLocation> _walls;
  const vector<pair<int, int>> _move_type = {
      {1, 0}, {0, -1}, {-1, 0}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
};
}  // namespace Road
