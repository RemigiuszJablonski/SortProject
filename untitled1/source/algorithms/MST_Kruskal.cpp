#include "../../include/algorithms/MST_Kruskal.h"
#include <algorithm>

int MST_Kruskal::findSet(int vertex, std::vector<int>& parent) {
    if (parent[vertex] == -1) return vertex;
    return parent[vertex] = findSet(parent[vertex], parent); // Path compression
}

std::vector<Edge> MST_Kruskal::findMST(const Graph& graph) {
    std::vector<Edge> edges = graph.getAllEdges();
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    std::vector<Edge> mst;
    std::vector<int> parent(graph.getVerticesCount(), -1);

    for (const Edge& edge : edges) {
        int u_root = findSet(edge.from, parent);
        int v_root = findSet(edge.to, parent);
        if (u_root != v_root) {
            mst.push_back(edge);
            parent[v_root] = u_root; // Union
        }
    }
    return mst;
}