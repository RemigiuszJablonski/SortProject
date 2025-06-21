#include "../../headers/utils/FileHandler.h"
#include <fstream>
#include <sstream>

Graph* FileHandler::loadGraphFromFile(const std::string& filename, bool directed) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open file");

    int edges, vertices;
    file >> edges >> vertices;

    Graph* graph = directed ? new ListGraph(vertices, true) : new ListGraph(vertices, false);

    for (int i = 0; i < edges; ++i) {
        int from, to, weight;
        file >> from >> to >> weight;
        graph->addEdge(from, to, weight);
    }
    return graph;
}

void FileHandler::saveGraphToFile(const Graph& graph, const std::string& filename) {
    std::ofstream file(filename);
    auto edges = graph.getAllEdges();
    file << edges.size() << " " << graph.getVerticesCount() << "\n";
    for (const auto& edge : edges) {
        file << edge.from << " " << edge.to << " " << edge.weight << "\n";
    }
}