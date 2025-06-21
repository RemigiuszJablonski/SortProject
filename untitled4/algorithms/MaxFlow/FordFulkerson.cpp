#include "FordFulkerson.h"
#include <queue>
#include <limits>
#include <algorithm>

bool FordFulkerson::bfsMatrix(const std::vector<std::vector<int>>& residualGraph,
                            int source, int sink, std::vector<int>& parent) {
    int V = residualGraph.size();
    std::vector<bool> visited(V, false);
    std::queue<int> q;

    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == sink) return true;
            }
        }
    }

    return false;
}

bool FordFulkerson::bfsList(const std::vector<std::vector<std::pair<int, int>>>& residualGraph,
                          int source, int sink, std::vector<int>& parent) {
    int V = residualGraph.size();
    std::vector<bool> visited(V, false);
    std::queue<int> q;

    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const auto& edge : residualGraph[u]) {
            int v = edge.first;
            int capacity = edge.second;
            if (!visited[v] && capacity > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == sink) return true;
            }
        }
    }

    return false;
}

int FordFulkerson::maxFlowMatrix(const Graph& graph, int source, int sink) {
    const auto& matrix = graph.getMatrix();
    int V = graph.getVertexCount();

    std::vector<std::vector<int>> residualGraph(V, std::vector<int>(V));
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            residualGraph[u][v] = matrix[u][v];
        }
    }

    std::vector<int> parent(V);
    int maxFlow = 0;

    while (bfsMatrix(residualGraph, source, sink, parent)) {
        int pathFlow = std::numeric_limits<int>::max();
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, residualGraph[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int FordFulkerson::maxFlowList(const Graph& graph, int source, int sink) {
    const auto& adjList = graph.getAdjList();
    int V = graph.getVertexCount();

    std::vector<std::vector<int>> residualGraph(V, std::vector<int>(V, 0));
    for (int u = 0; u < V; ++u) {
        for (const auto& edge : adjList[u]) {
            int v = edge.first;
            residualGraph[u][v] = edge.second;
        }
    }

    std::vector<int> parent(V);
    int maxFlow = 0;

    while (bfsMatrix(residualGraph, source, sink, parent)) {
        int pathFlow = std::numeric_limits<int>::max();
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, residualGraph[u][v]);
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}