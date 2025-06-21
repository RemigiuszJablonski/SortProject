#include "../../headers/algorithms/SP_Dijkstra.h"
#include <queue>
#include <limits>
#include <iostream>

std::vector<int> SP_Dijkstra::findShortestPath(const Graph& graph, int source) {
    int vertices = graph.getVerticesCount();
    std::vector<int> dist(vertices, std::numeric_limits<int>::max());
    std::vector<int> prev(vertices, -1);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    dist[source] = 0;
    pq.emplace(0, source);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const Edge& edge : graph.getNeighbors(u)) {
            int v = edge.to;
            int weight = edge.weight;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }

    // Rekonstrukcja ścieżek (opcjonalnie)
    return dist;
}

void SP_Dijkstra::printPath(const std::vector<int>& prev, int target) {
    if (prev[target] != -1) {
        printPath(prev, prev[target]);
    }
    std::cout << target << " ";
}