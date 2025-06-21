#include "Dijkstra.h"
#include <limits>
#include <vector>

std::pair<std::vector<int>, std::vector<int>> Dijkstra::shortestPathMatrix(const Graph& graph, int start) {
    const auto& matrix = graph.getMatrix();
    int V = graph.getVertexCount();
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::vector<int> parent(V, -1);
    std::vector<bool> visited(V, false);

    dist[start] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        if (dist[u] == std::numeric_limits<int>::max()) break;
        visited[u] = true;

        for (int v = 0; v < V; ++v) {
            if (matrix[u][v] && !visited[v] && dist[u] + matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + matrix[u][v];
                parent[v] = u;
            }
        }
    }

    return {dist, parent};
}

std::pair<std::vector<int>, std::vector<int>> Dijkstra::shortestPathList(const Graph& graph, int start) {
    const auto& adjList = graph.getAdjList();
    int V = graph.getVertexCount();
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    std::vector<int> parent(V, -1);
    std::vector<bool> visited(V, false);

    dist[start] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        if (dist[u] == std::numeric_limits<int>::max()) break;
        visited[u] = true;

        for (const auto& edge : adjList[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    return {dist, parent};
}