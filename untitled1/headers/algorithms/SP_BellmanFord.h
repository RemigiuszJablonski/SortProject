#ifndef BELLMAN_FORD_SP_H
#define BELLMAN_FORD_SP_H

#include "../graphs/Graph.h"
#include <vector>

class SP_BellmanFord {
public:
    static std::pair<std::vector<int>, std::vector<int>> findShortestPath(const Graph& graph, int source);
    static std::string getName() { return "Bellman-Ford Algorithm"; }
};

#endif // BELLMAN_FORD_SP_H