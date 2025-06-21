#ifndef GRAPH_H
#define GRAPH_H

#include "Graph.h"
#include <vector>
#include <list>

class Graph {
protected:
    int vertexCount;
    bool isDirected;

public:
    Graph(int V, bool directed) : vertexCount(V), isDirected(directed) {}
    virtual ~Graph() = default;

    virtual void addEdge(int u, int v, int weight) = 0;
    virtual int getWeight(int u, int v) const = 0;
    virtual int getVertexCount() const { return vertexCount; }
    virtual bool getDirected() const { return isDirected; }
    virtual void print() const = 0;

    // Dla MST
    virtual std::vector<std::tuple<int, int, int>> getAllEdges() const = 0;

    // Dla algorytmów ścieżkowych
    virtual std::vector<std::pair<int, int>> getAdjacent(int v) const = 0;
};

#endif // GRAPH_H
