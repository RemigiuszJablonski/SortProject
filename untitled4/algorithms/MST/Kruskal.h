#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../../Graph.h"
#include <vector>
#include <utility>

class Kruskal {
public:
    static std::vector<std::pair<int, int>> findMSTMatrix(const Graph& graph);
    static std::vector<std::pair<int, int>> findMSTList(const Graph& graph);
};

#endif // KRUSKAL_H