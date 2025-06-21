#include "BellmanFord.h"
#include <limits>
#include <vector>

std::pair<std::vector<int>, std::vector<int>> BellmanFord::shortestPathMatrix(const Graph& graph, int start) {
    const auto& matrix = graph.getMatrix();
    int V = graph.getVertexCount();
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::vector<int> parent(V, -1);

    dist[start] = 0;

    for (int i = 1; i < V; ++i) {
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                if (matrix[u][v] && dist[u] != std::numeric_limits<int>::max() &&
                    dist[u] + matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + matrix[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (matrix[u][v] && dist[u] != std::numeric_limits<int>::max() &&
                dist[u] + matrix[u][v] < dist[v]) {
                return {{}, {}}; // Negative cycle
            }
        }
    }

    return {dist, parent};
}

std::pair<std::vector<int>, std::vector<int>> BellmanFord::shortestPathList(const Graph& graph, int start) {
    const auto& adjList = graph.getAdjList();
    int V = graph.getVertexCount();
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::vector<int> parent(V, -1);

    dist[start] = 0;

    for (int i = 1; i < V; ++i) {
        for (int u = 0; u < V; ++u) {
            for (const auto& edge : adjList[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[u] != std::numeric_limits<int>::max() &&
                    dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < V; ++u) {
        for (const auto& edge : adjList[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] != std::numeric_limits<int>::max() &&
                dist[u] + weight < dist[v]) {
                return {{}, {}}; // Negative cycle
            }
        }
    }

    return {dist, parent};
}