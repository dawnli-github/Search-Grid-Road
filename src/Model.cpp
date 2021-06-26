/**
 * @file Model.cpp
 * @author Dawn Li (dawnli619215645@gmail.com)
 * @brief Model
 * @version 0.1
 * @date 2021-06-25
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "../include/Model.h"

using namespace std;

namespace Road {
// template <typename Graph, typename Location>
// void Model::a_star_search(Graph graph, Location start, Location goal,
//                           function<int(Location a, Location b)> heuristic,
//                           unordered_map<Location, Location>& came_from,
//                           unordered_map<Location, int>& cost_so_far) {
//   PriorityQueue<Location, int> frontier;
//   vector<Location> neighbors;
//   frontier.put(start, 0);

//   came_from[start] = start;
//   cost_so_far[start] = 0;

//   while (!frontier.empty()) {
//     Location current = frontier.get();

//     if (current == goal) {
//       break;
//     }

//     graph.get_neighbors(current, neighbors);
//     for (Location next : neighbors) {
//       int new_cost = cost_so_far[current] + graph.cost(current, next);
//       if (cost_so_far.find(next) == cost_so_far.end() ||
//           new_cost < cost_so_far[next]) {
//         cost_so_far[next] = new_cost;
//         int priority = new_cost + heuristic(next, goal);
//         frontier.put(next, priority);
//         came_from[next] = current;
//       }
//     }
//   }
// }
}  // namespace Road