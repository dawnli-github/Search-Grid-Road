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

#include <memory.h>

#include <chrono>
#include <functional>
#include <iomanip>

#include "Graph.h"
#include "PriorityQueue.h"
#include "Utility.h"

using namespace std;

namespace road {

template <typename Location>
class AbstractModel {
 public:
  AbstractModel() = default;
  AbstractModel(const AbstractModel& other) = delete;
  AbstractModel(AbstractModel&& other) = delete;
  AbstractModel& operator=(AbstractModel const&) = delete;
  AbstractModel& operator=(AbstractModel&&) = delete;
  virtual ~AbstractModel() = default;

  virtual void printModelName(){};
  virtual void run(){};
  virtual double get_run_time() const = 0;
  virtual vector<Location> get_path() const = 0;
};

template <typename Graph, typename Location>
class AStarModel : public AbstractModel<Location> {
 public:
  AStarModel(Graph graph, Location start, Location goal,
             function<double(Location a, Location b)> heuristic)
      : _graph(graph), _start(start), _goal(goal), _heuristic(heuristic) {
    printModelName();
    run();
  }
  void printModelName() { cout << "A* Model Flow" << endl; }
  // A* algorithm
  void run() final {
    auto time_start = chrono::system_clock::now();
    PriorityQueue<Location, double> frontier;
    frontier.put(_start, 0);
    unordered_map<Location, Location> came_from;
    unordered_map<Location, double> cost_so_far;
    came_from[_start] = _start;
    cost_so_far[_start] = 0;

    while (!frontier.empty()) {
      Location current = frontier.get();

      if (current == _goal) {
        break;
      }
      for (Location next : _graph.get_neighbors(current)) {
        double new_cost = cost_so_far[current] + _graph.cost(current, next);
        if (cost_so_far.find(next) == cost_so_far.end() ||
            new_cost < cost_so_far[next]) {
          cost_so_far[next] = new_cost;
          double priority = new_cost + _heuristic(next, _goal);
          frontier.put(next, priority);
          came_from[next] = current;
        }
      }
    }
    auto time_end = chrono::system_clock::now();
    auto time_duration =
        chrono::duration_cast<chrono::microseconds>(time_end - time_start);
    _run_time = double(time_duration.count()) *
                chrono::microseconds::period::num /
                chrono::microseconds::period::den;
    // Reconstruct path
    Location current = _goal;
    while (current != _start) {
      _path.push_back(current);
      current = came_from[current];
    }
    _path.push_back(_start);
    reverse(_path.begin(), _path.end());
  }
  // Getter
  double get_run_time() const final { return _run_time; }
  vector<Location> get_path() const { return _path; }

 private:
  Graph _graph;
  Location _start;
  Location _goal;
  function<double(Location a, Location b)> _heuristic;
  vector<Location> _path;
  double _run_time = 0;
};

template <typename Graph, typename Location>
class DijkstraModel : public AbstractModel<Location> {
 public:
  DijkstraModel(Graph graph, Location start, Location goal)
      : _graph(graph), _start(start), _goal(goal) {
    printModelName();
    run();
  }
  void printModelName() { cout << "Dijkstra Model Flow" << endl; }
  // Dijkstra algorithm
  void run() {
    auto time_start = chrono::system_clock::now();
    PriorityQueue<Location, double> frontier;
    frontier.put(_start, 0);
    unordered_map<Location, Location> came_from;
    unordered_map<Location, double> cost_so_far;
    came_from[_start] = _start;
    cost_so_far[_start] = 0;

    while (!frontier.empty()) {
      Location current = frontier.get();

      if (current == _goal) {
        break;
      }
      for (Location next : _graph.get_neighbors(current)) {
        double new_cost = cost_so_far[current] + _graph.cost(current, next);
        if (cost_so_far.find(next) == cost_so_far.end() ||
            new_cost < cost_so_far[next]) {
          cost_so_far[next] = new_cost;
          double priority = new_cost;
          frontier.put(next, priority);
          came_from[next] = current;
        }
      }
    }
    auto time_end = chrono::system_clock::now();
    auto time_duration =
        chrono::duration_cast<chrono::microseconds>(time_end - time_start);
    _run_time = double(time_duration.count()) *
                chrono::microseconds::period::num /
                chrono::microseconds::period::den;
    // Reconstruct path
    Location current = _goal;
    while (current != _start) {
      _path.push_back(current);
      current = came_from[current];
    }
    _path.push_back(_start);
    reverse(_path.begin(), _path.end());
  }
  // Getter
  double get_run_time() const final { return _run_time; }
  vector<Location> get_path() const { return _path; }

 private:
  Graph _graph;
  Location _start;
  Location _goal;
  vector<Location> _path;
  double _run_time = 0;
};

template <typename Graph, typename Location>
class Factory {
 public:
  Factory(Graph graph, Location start, Location goal)
      : _graph(graph), _start(start), _goal(goal) {
    cout << "Factory is running" << endl << endl;
  }
  unique_ptr<AbstractModel<Location>> setModel(string& model_name,
                                                    string& heuristic_name) {
    unique_ptr<AbstractModel<Location>> model = nullptr;
    if (model_name == "A*" && heuristic_name == "manhattan") {
      model = make_unique<AStarModel<Graph, Location>>(
          _graph, _start, _goal, Heuristic::manhattan);
    } else if (model_name == "A*" && heuristic_name == "optManhattan") {
      model = make_unique<AStarModel<Graph, Location>>(
          _graph, _start, _goal, Heuristic::optManhattan);
    } else if (model_name == "Dijkstra") {
      model = make_unique<DijkstraModel<Graph, Location>>(_graph, _start,
                                                               _goal);
    }
    return model;
  }

 private:
  Graph _graph;
  Location _start;
  Location _goal;
};

}  // namespace road
