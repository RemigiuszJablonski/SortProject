#include "../../headers/graphs/ListGraph.h"
#include <iostream>
#include <stdexcept>

ListGraph::ListGraph(int vertices, bool directed)
    : vertices_(vertices), directed_(directed) {
    if (vertices <= 0) throw std::invalid_argument("Number of vertices must be positive");
    adjacency_list_.resize(vertices);
}

void ListGraph::addEdge(int from, int to, int weight) {
    if (from < 0 || from >= vertices_ || to < 0 || to >= vertices_) {
        throw std::out_of_range("Vertex index out of bounds");
    }
    adjacency_list_[from].emplace_back(to, weight);
    if (!directed_) {
        adjacency_list_[to].emplace_back(from, weight);
    }
}

const std::vector<Edge>& ListGraph::getNeighbors(int vertex) const {
    return adjacency_list_[vertex];
}

void ListGraph::print() const {
    for (int i = 0; i < vertices_; ++i) {
        std::cout << "Vertex " << i << ": ";
        for (const Edge& edge : adjacency_list_[i]) {
            std::cout << "-> " << edge.to << " (w:" << edge.weight << ") ";
        }
        std::cout << std::endl;
    }
}