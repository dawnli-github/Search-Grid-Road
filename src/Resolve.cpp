/**
 * @file Resolve.cpp
 * @author Dawn Li (dawnli619215645@gmail.com)
 * @brief Resolve
 * @version 0.1
 * @date 2021-06-24
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "../include/Resolve.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

namespace Road {

void Resolve::run() {
  // Build Dijkstra model
  cout << endl << "Dijkstra Model Flow" << endl << endl;
  unordered_map<GridLocation, GridLocation> dj_came_from;
  unordered_map<GridLocation, int> dj_cost_so_far;
  Model::dijkstra_search<Graph, GridLocation>(_graph, _start, _goal,
                                              dj_came_from, dj_cost_so_far);
  vector<GridLocation> dj_path = reconstruct_path(_start, _goal, dj_came_from);
  draw(_graph, 3, &dj_path);
  cout << endl << "The Model Cost :" << get_cost(dj_path) << endl;
  cout << endl
       << "----------------------------------------------------" << endl;
  // Build A* model
  cout << endl << "A* Model Flow" << endl << endl;
  unordered_map<GridLocation, GridLocation> came_from;
  unordered_map<GridLocation, int> cost_so_far;
  Model::a_star_search<Graph, GridLocation>(
      _graph, _start, _goal, Heuristic::manhattan, came_from, cost_so_far);
  vector<GridLocation> path = reconstruct_path(_start, _goal, came_from);
  draw(_graph, 3, &path);
  cout << endl << "The Model Cost :" << get_cost(path) << endl;
  cout << endl
       << "----------------------------------------------------" << endl;
  // Build A* opt model
  cout << endl << "A* Optimized Model Flow" << endl << endl;
  unordered_map<GridLocation, GridLocation> opt_came_from;
  unordered_map<GridLocation, int> opt_cost_so_far;
  Model::a_star_search<Graph, GridLocation>(_graph, _start, _goal,
                                            Heuristic::optManhattan,
                                            opt_came_from, opt_cost_so_far);
  vector<GridLocation> opt_path =
      reconstruct_path(_start, _goal, opt_came_from);
  draw(_graph, 3, &opt_path);
  cout << endl << "The Model Cost :" << get_cost(opt_path) << endl;
  cout << endl
       << "----------------------------------------------------" << endl;
}

vector<GridLocation> Resolve::reconstruct_path(
    GridLocation start, GridLocation goal,
    unordered_map<GridLocation, GridLocation> came_from) {
  vector<GridLocation> path;
  GridLocation current = goal;
  while (current != start) {
    path.push_back(current);
    current = came_from[current];
  }
  path.push_back(start);  // optional
  reverse(path.begin(), path.end());
  return path;
}

void Resolve::draw(const Graph& graph, int field_width,
                   vector<GridLocation>* path) {
  for (int y = 0; y != graph.get_height(); ++y) {
    for (int x = 0; x != graph.get_width(); ++x) {
      GridLocation id{x, y};
      cout << left << setw(field_width);
      if (graph.get_walls().find(id) != graph.get_walls().end()) {
        cout << "\033[41m#\033[0m"
             << "  ";
      } else if (id == path->front()) {
        cout << "\033[34mS\033[0m"
             << "  ";
      } else if (id == path->back()) {
        cout << "\033[36mE\033[0m"
             << "  ";
      } else if (path != nullptr &&
                 find(path->begin(), path->end(), id) != path->end()) {
        cout << "\033[32m@\033[0m"
             << "  ";
      } else {
        cout << "\033[32m.\033[0m"
             << "  ";
      }
    }
    cout << '\n';
  }
}
}  // namespace Road
