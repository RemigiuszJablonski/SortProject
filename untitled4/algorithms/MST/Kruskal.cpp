#include "Kruskal.h"
#include <algorithm>
#include <vector>

std::vector<std::pair<int, int>> Kruskal::findMSTMatrix(const Graph& graph) {
    const auto& matrix = graph.getMatrix();
    int V = graph.getVertexCount();
    std::vector<std::pair<int, std::pair<int, int>>> edges;

    for (int u = 0; u < V; ++u) {
        for (int v = u + 1; v < V; ++v) {
            if (matrix[u][v] != 0) {
                edges.push_back({matrix[u][v], {u, v}});
            }
        }
    }

    std::sort(edges.begin(), edges.end());

    std::vector<int> parent(V);
    for (int i = 0; i < V; ++i) parent[i] = i;

    auto find = [&parent](int u) {
        while (parent[u] != u) {
            parent[u] = parent[parent[u]];
            u = parent[u];
        }
        return u;
    };

    std::vector<std::pair<int, int>> result;
    for (const auto& edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        int set_u = find(u);
        int set_v = find(v);

        if (set_u != set_v) {
            result.push_back({u, v});
            parent[set_v] = set_u;
        }
    }

    return result;
}

std::vector<std::pair<int, int>> Kruskal::findMSTList(const Graph& graph) {
    const auto& adjList = graph.getAdjList();
    int V = graph.getVertexCount();
    std::vector<std::pair<int, std::pair<int, int>>> edges;

    for (int u = 0; u < V; ++u) {
        for (const auto& edge : adjList[u]) {
            int v = edge.first;
            if (u < v) {
                edges.push_back({edge.second, {u, v}});
            }
        }
    }

    std::sort(edges.begin(), edges.end());

    std::vector<int> parent(V);
    for (int i = 0; i < V; ++i) parent[i] = i;

    auto find = [&parent](int u) {
        while (parent[u] != u) {
            parent[u] = parent[parent[u]];
            u = parent[u];
        }
        return u;
    };

    std::vector<std::pair<int, int>> result;
    for (const auto& edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        int set_u = find(u);
        int set_v = find(v);

        if (set_u != set_v) {
            result.push_back({u, v});
            parent[set_v] = set_u;
        }
    }

    return result;
}