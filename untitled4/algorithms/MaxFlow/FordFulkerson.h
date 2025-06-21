#ifndef FORDFULKERSON_H
#define FORDFULKERSON_H

#include "../../Graph.h"
#include <vector>

class FordFulkerson {
public:
    static int maxFlowMatrix(const Graph& graph, int source, int sink);
    static int maxFlowList(const Graph& graph, int source, int sink);

private:
    static bool bfsMatrix(const std::vector<std::vector<int>>& residualGraph,
                        int source, int sink, std::vector<int>& parent);
    static bool bfsList(const std::vector<std::vector<std::pair<int, int>>>& residualGraph,
                      int source, int sink, std::vector<int>& parent);
};

#endif // FORDFULKERSON_H