#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include "../../Graph.h"
#include <vector>
#include <utility>

class BellmanFord {
public:
    static std::pair<std::vector<int>, std::vector<int>> shortestPathMatrix(const Graph& graph, int start);
    static std::pair<std::vector<int>, std::vector<int>> shortestPathList(const Graph& graph, int start);
};

#endif // BELLMANFORD_H