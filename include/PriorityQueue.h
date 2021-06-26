/**
 * @file PriorityQueue.h
 * @author Dawn Li (dawnli619215645@gmail.com)
 * @brief PriorityQueue
 * @version 0.1
 * @date 2021-06-24
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

namespace Road {
template <typename T, typename priority_t>
struct PriorityQueue {
  typedef pair<priority_t, T> priority_element;
  priority_queue<priority_element, vector<priority_element>, greater<priority_element>> elements;

  inline bool empty() const { return elements.empty(); }

  inline void put(T item, priority_t priority) {
    elements.emplace(priority, item);
  }

  T get() {
    T best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};
}  // namespace Road