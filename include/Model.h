/**
 * @file Model.h
 * @author Dawn Li (dawnli619215645@gmail.com)
 * @brief Model
 * @version 0.1
 * @date 2021-06-25
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <functional>

#include "Graph.h"
#include "PriorityQueue.h"

using namespace std;

namespace road {
class Model {
 public:
  // A* algorithm
  template <typename Graph, typename Location>
  static void a_star_search(Graph graph, Location start, Location goal,
                            function<int(Location a, Location b)> heuristic,
                            unordered_map<Location, Location>& came_from,
                            unordered_map<Location, int>& cost_so_far) {
    PriorityQueue<Location, int> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
      Location current = frontier.get();

      if (current == goal) {
        break;
      }
      for (Location next : graph.get_neighbors(current)) {
        int new_cost = cost_so_far[current] + graph.cost(current, next);
        if (cost_so_far.find(next) == cost_so_far.end() ||
            new_cost < cost_so_far[next]) {
          cost_so_far[next] = new_cost;
          int priority = new_cost + heuristic(next, goal);
          frontier.put(next, priority);
          came_from[next] = current;
        }
      }
    }
  }

  // Dijkstra algorithm
  template <typename Graph, typename Location>
  static void dijkstra_search(Graph graph, Location start, Location goal,
                              std::unordered_map<Location, Location>& came_from,
                              std::unordered_map<Location, int>& cost_so_far) {
    PriorityQueue<Location, int> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
      Location current = frontier.get();

      if (current == goal) {
        break;
      }

      for (Location next : graph.get_neighbors(current)) {
        int new_cost = cost_so_far[current] + graph.cost(current, next);
        if (cost_so_far.find(next) == cost_so_far.end() ||
            new_cost < cost_so_far[next]) {
          cost_so_far[next] = new_cost;
          came_from[next] = current;
          frontier.put(next, new_cost);
        }
      }
    }
  }

 private:
};
}  // namespace road
