#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include "Graph.h"
#include <vector>

class MatrixGraph : public Graph {
    int** adjacencyMatrix;

public:
    MatrixGraph(int V, bool directed);
    ~MatrixGraph() override;

    void addEdge(int u, int v, int weight) override;
    int getWeight(int u, int v) const override;
    void print() const override;

    std::vector<std::tuple<int, int, int>> getAllEdges() const override;
    std::vector<std::pair<int, int>> getAdjacent(int v) const override;
};

#endif // MATRIX_GRAPH_H