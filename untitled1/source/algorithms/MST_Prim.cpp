#include "../../include/algorithms/MST_Prim.h"
#include <limits>
#include <queue>

std::vector<Edge> MST_Prim::findMST(const Graph& graph) {
    int vertices = graph.getVerticesCount();
    std::vector<Edge> mst;
    std::vector<bool> visited(vertices, false);
    std::vector<int> min_weight(vertices, std::numeric_limits<int>::max());
    std::vector<int> parent(vertices, -1);

    min_weight[0] = 0; // Start from vertex 0

    for (int i = 0; i < vertices; ++i) {
        int u = -1;
        for (int j = 0; j < vertices; ++j) {
            if (!visited[j] && (u == -1 || min_weight[j] < min_weight[u])) {
                u = j;
            }
        }
        if (min_weight[u] == std::numeric_limits<int>::max()) {
            throw std::runtime_error("Graph is not connected");
        }
        visited[u] = true;
        if (parent[u] != -1) {
            mst.emplace_back(parent[u], u, min_weight[u]);
        }
        for (const Edge& edge : graph.getNeighbors(u)) {
            if (!visited[edge.to] && edge.weight < min_weight[edge.to]) {
                min_weight[edge.to] = edge.weight;
                parent[edge.to] = u;
            }
        }
    }
    return mst;
}