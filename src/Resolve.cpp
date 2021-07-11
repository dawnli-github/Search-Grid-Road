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

#include "Resolve.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std;

namespace road {

void Resolve::run(string model_name, string heuristic_name) {
  unique_ptr<Factory<Graph, GridLocation>> factory =
      make_unique<Factory<Graph, GridLocation>>(_graph, _start, _goal);
  auto model = factory->setModel(model_name, heuristic_name);
  cout << endl << "The Heuristic Type : " << heuristic_name << endl << endl;
  vector<GridLocation> path = model->get_path();
  draw(_graph, &path);
  cout << endl << "The Model Cost :" << get_cost(path) << endl;
  cout << endl
       << "The Model Running Time :" << model->get_run_time() << "s" << endl;
  cout << endl
       << "----------------------------------------------------" << endl;
}

void Resolve::draw(const Graph& graph, vector<GridLocation>* path) {
  for (int y = 0; y != graph.get_height(); ++y) {
    for (int x = 0; x != graph.get_width(); ++x) {
      GridLocation id{x, y};
      cout << left << setw(3);
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
}  // namespace road
