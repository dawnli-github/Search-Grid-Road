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

namespace road {
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
  void set_wall(const GridLocation& wall) { _graph.set_wall(wall); }
  void set_start(const GridLocation start) { _start = start; }
  void set_goal(const GridLocation goal) { _goal = goal; }
  // Work flow///
  void run(string model_name, string heuristic_name);
  // Compute Cost
  static double get_cost(vector<GridLocation> path) {
    double cost = 0;
    for (long unsigned int i = 0; i < path.size() - 1; ++i) {
      cost += (path[i + 1].x - path[i].x) * (path[i + 1].y - path[i].y) == 0
                  ? 1.0
                  : sqrt(2);
    }
    return cost;
  }
  // Get
  GridLocation get_start() const { return _start; }
  GridLocation get_goal() const { return _goal; }
  // Draw
  static void draw(const Graph& graph, vector<GridLocation>* path);

 private:
  GridLocation _start;
  GridLocation _goal;
  Graph _graph;
};
}  // namespace road
