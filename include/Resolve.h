/**
 * @file Resolve.h
 * @author Dawn Li (dawnli619215645@gmail.com)
 * @brief Resolve
 * @version 0.1
 * @date 2021-06-24
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include "Graph.h"
#include "Model.h"
#include "PriorityQueue.h"
#include "Utility.h"

using namespace std;

namespace Road {
class Resolve {
 public:
  // Set
  void set_size(const int width, const int height) {
    _graph.init(width, height);
  }
  void set_walls(const vector<GridLocation>& walls) {
    for (auto wall : walls) {
      _graph.set_wall(wall);
    }
  }
  void set_start(const GridLocation start) { _start = start; }
  void set_goal(const GridLocation goal) { _goal = goal; }
  // Work flow///
  void run();
  // Compute Cost
  static double get_cost(vector<GridLocation> path) {
    double cost = 0;
    for (long unsigned int i = 0; i < path.size() - 1; ++i) {
      cost +=
          abs(path[i + 1].x - path[i].x) + abs(path[i + 1].y - path[i].y) == 2
              ? sqrt(2)
              : 1.0;
    }
    return cost;
  }
  // Get
  GridLocation get_start() const { return _start; }
  GridLocation get_goal() const { return _goal; }
  // Reconstruct path
  static vector<GridLocation> reconstruct_path(
      GridLocation start, GridLocation goal,
      unordered_map<GridLocation, GridLocation> came_from);
  // Draw
  static void draw(const Graph& graph, int field_width,
                   vector<GridLocation>* path);

 private:
  GridLocation _start;
  GridLocation _goal;
  Graph _graph;
};
}  // namespace Road