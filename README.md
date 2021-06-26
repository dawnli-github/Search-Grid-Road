# Search Grid Road

A program for solving the shortest path between two points in the grid.

## 1. Algorithm List

### Dijkstra Model

Dijkstra is a pathfinding algorithm, and use the the movement cost f(x) as the overall evaluation criteria, the configuration of this model is as follows:

* f(x): The distance between the current position and the starting point.

### A* Model

A* algorithm uses the combination of the movement cost f(x) and the estimated cost h(x) as the overall evaluation criteria, the configuration of this model is as follows:

* f(x): The distance between the current position and the starting point.
* h(x): The Manhattan distance between the current position and the endding point.
### Optimized A* Model

Optimize performance by using different functions, the configuration of this model is as follows:

* f(x): The distance between the current position and the starting point.
* h(x): The Integrated distance between the current position and the endding point.

Among them, the comprehensive distance is the comprehensive consideration of Euclidean distance and Manhattan distance.

## 2. Config

```shell
git clone https://github.com/dawnli-github/Search-Grid-Road.git

cd Seach-Grid-Road && mkdir build && cmake .. && make
```

## 3. Demonstration

```shell
cd ../bin/

./Demonstration
```
