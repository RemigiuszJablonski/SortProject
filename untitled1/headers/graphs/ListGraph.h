#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H

#include "Graph.h"
#include <vector>
#include <list>

class ListGraph : public Graph {
    std::vector<std::list<std::pair<int, int>>> adjacencyList;

public:
    ListGraph(int V, bool directed);

    void addEdge(int u, int v, int weight) override;
    int getWeight(int u, int v) const override;
    void print() const override;

    std::vector<std::tuple<int, int, int>> getAllEdges() const override;
    std::vector<std::pair<int, int>> getAdjacent(int v) const override;
};

#endif // LIST_GRAPH_H