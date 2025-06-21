#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "../../Graph.h"
#include <vector>
#include <utility>

class Dijkstra {
public:
    static std::pair<std::vector<int>, std::vector<int>> shortestPathMatrix(const Graph& graph, int start);
    static std::pair<std::vector<int>, std::vector<int>> shortestPathList(const Graph& graph, int start);
};

#endif // DIJKSTRA_H