#ifndef DIJKSTRA_SP_H
#define DIJKSTRA_SP_H

#include "../graphs/Graph.h"
#include <vector>

class SP_Dijkstra {
public:
    static std::pair<std::vector<int>, std::vector<int>> findShortestPath(const Graph& graph, int source);
    static std::string getName() { return "Dijkstra's Algorithm"; }
};

#endif // DIJKSTRA_SP_H