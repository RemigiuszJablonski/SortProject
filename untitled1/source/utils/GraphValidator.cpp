#include "../../headers/utils/GraphValidator.h"
#include <queue>

bool GraphValidator::isConnected(const Graph& graph) {
    int vertices = graph.getVerticesCount();
    if (vertices == 0) return true;

    std::vector<bool> visited(vertices, false);
    std::queue<int> q;
    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const Edge& edge : graph.getNeighbors(u)) {
            if (!visited[edge.to]) {
                visited[edge.to] = true;
                q.push(edge.to);
            }
        }
    }

    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}

bool GraphValidator::hasNegativeWeights(const Graph& graph) {
    for (const Edge& edge : graph.getAllEdges()) {
        if (edge.weight < 0) return true;
    }
    return false;
}