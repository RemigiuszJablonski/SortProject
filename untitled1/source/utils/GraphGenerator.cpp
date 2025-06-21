#include "../../include/utils/GraphGenerator.h"
#include <random>
#include <algorithm>

Graph* GraphGenerator::generateGraph(int vertices, int density, bool directed) {
    Graph* graph = directed ? new ListGraph(vertices, true) : new ListGraph(vertices, false);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> weight_dist(1, 100);

    // Najpierw generujemy drzewo rozpinające (gwarancja spójności)
    for (int i = 1; i < vertices; ++i) {
        int parent = std::uniform_int_distribution<>(0, i-1)(gen);
        int weight = weight_dist(gen);
        graph->addEdge(parent, i, weight);
    }

    // Dodajemy pozostałe krawędzie do wymaganej gęstości
    int max_possible_edges = directed ? vertices * (vertices - 1) : vertices * (vertices - 1) / 2;
    int target_edges = max_possible_edges * density / 100;
    int edges_to_add = target_edges - (vertices - 1);

    while (edges_to_add > 0) {
        int u = std::uniform_int_distribution<>(0, vertices-1)(gen);
        int v = std::uniform_int_distribution<>(0, vertices-1)(gen);
        if (u != v && !graph->hasEdge(u, v)) {
            graph->addEdge(u, v, weight_dist(gen));
            edges_to_add--;
        }
    }
    return graph;
}