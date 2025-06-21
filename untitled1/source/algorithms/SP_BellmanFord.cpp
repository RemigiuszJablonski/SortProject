#include "../../headers/algorithms/SP_BellmanFord.h"
#include <limits>
#include <iostream>

bool SP_BellmanFord::findShortestPath(const Graph& graph, int source, std::vector<int>& dist) {
    int vertices = graph.getVerticesCount();
    dist.assign(vertices, std::numeric_limits<int>::max());
    dist[source] = 0;
    std::vector<Edge> edges = graph.getAllEdges();

    // Relaksacja krawędzi V-1 razy
    for (int i = 1; i < vertices; ++i) {
        for (const Edge& edge : edges) {
            if (dist[edge.from] != std::numeric_limits<int>::max() &&
                dist[edge.to] > dist[edge.from] + edge.weight) {
                dist[edge.to] = dist[edge.from] + edge.weight;
                }
        }
    }

    // Sprawdzenie cykli o ujemnej wadze
    for (const Edge& edge : edges) {
        if (dist[edge.from] != std::numeric_limits<int>::max() &&
            dist[edge.to] > dist[edge.from] + edge.weight) {
            return false; // Wykryto cykl ujemny
            }
    }
    return true;
}