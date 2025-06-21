#include "Prim.h"
#include <limits>
#include <vector>

std::vector<std::pair<int, int>> Prim::findMSTMatrix(const Graph& graph) {
    const auto& matrix = graph.getMatrix();
    int V = graph.getVertexCount();
    std::vector<std::pair<int, int>> result;

    std::vector<int> parent(V, -1);
    std::vector<int> key(V, std::numeric_limits<int>::max());
    std::vector<bool> inMST(V, false);

    key[0] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        for (int v = 0; v < V; ++v) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        inMST[u] = true;

        for (int v = 0; v < V; ++v) {
            if (matrix[u][v] && !inMST[v] && matrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = matrix[u][v];
            }
        }
    }

    for (int i = 1; i < V; ++i) {
        result.emplace_back(parent[i], i);
    }

    return result;
}

std::vector<std::pair<int, int>> Prim::findMSTList(const Graph& graph) {
    const auto& adjList = graph.getAdjList();
    int V = graph.getVertexCount();
    std::vector<std::pair<int, int>> result;

    std::vector<int> parent(V, -1);
    std::vector<int> key(V, std::numeric_limits<int>::max());
    std::vector<bool> inMST(V, false);

    key[0] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        for (int v = 0; v < V; ++v) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        inMST[u] = true;

        for (const auto& edge : adjList[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (!inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    for (int i = 1; i < V; ++i) {
        result.emplace_back(parent[i], i);
    }

    return result;
}