#ifndef PRIM_MST_H
#define PRIM_MST_H

#include "../graphs/Graph.h"
#include <vector>
#include <tuple>

class MST_Prim {
public:
    static std::vector<std::tuple<int, int, int>> findMST(const Graph& graph);
    static std::string getName() { return "Prim's Algorithm"; }
};

#endif // PRIM_MST_H