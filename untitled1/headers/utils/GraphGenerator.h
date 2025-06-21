#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include "../graphs/Graph.h"
#include <memory>

class GraphGenerator {
public:
    static std::unique_ptr<Graph> generate(int vertexCount, float density, bool directed, bool matrixRepresentation);
    static std::unique_ptr<Graph> generateConnectedGraph(int vertexCount, float density, bool directed, bool matrixRepresentation);
};

#endif // GRAPH_GENERATOR_H