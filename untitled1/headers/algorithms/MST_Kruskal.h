#ifndef KRUSKAL_MST_H
#define KRUSKAL_MST_H

#include "../graphs/Graph.h"
#include <vector>
#include <tuple>


class MST_Kruskal {
public:
    static std::vector<std::tuple<int, int, int>> findMST(const Graph& graph);
    static std::string getName() { return "Kruskal's Algorithm"; }
};

#endif // KRUSKAL_MST_H