#include "../../include/graphs/MatrixGraph.h"
#include <iostream>
#include <stdexcept>

MatrixGraph::MatrixGraph(int vertices, bool directed)
    : vertices_(vertices), directed_(directed) {
    if (vertices <= 0) throw std::invalid_argument("Number of vertices must be positive");

    matrix_ = new int*[vertices_];
    for (int i = 0; i < vertices_; ++i) {
        matrix_[i] = new int[vertices_];
        for (int j = 0; j < vertices_; ++j) {
            matrix_[i][j] = 0; // 0 oznacza brak krawędzi
        }
    }
}

MatrixGraph::~MatrixGraph() {
    for (int i = 0; i < vertices_; ++i) {
        delete[] matrix_[i];
    }
    delete[] matrix_;
}

void MatrixGraph::addEdge(int from, int to, int weight) {
    if (from < 0 || from >= vertices_ || to < 0 || to >= vertices_) {
        throw std::out_of_range("Vertex index out of bounds");
    }
    matrix_[from][to] = weight;
    if (!directed_) {
        matrix_[to][from] = weight;
    }
}

int MatrixGraph::getWeight(int from, int to) const {
    return matrix_[from][to];
}

void MatrixGraph::print() const {
    for (int i = 0; i < vertices_; ++i) {
        for (int j = 0; j < vertices_; ++j) {
            std::cout << matrix_[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}