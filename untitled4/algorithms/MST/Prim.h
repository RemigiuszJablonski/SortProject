#ifndef PRIM_H
#define PRIM_H

#include "../../Graph.h"
#include <vector>
#include <utility>

class Prim {
public:
    static std::vector<std::pair<int, int>> findMSTMatrix(const Graph& graph);
    static std::vector<std::pair<int, int>> findMSTList(const Graph& graph);
};

#endif // PRIM_H