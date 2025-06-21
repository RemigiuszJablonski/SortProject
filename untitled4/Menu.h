#ifndef MENU_H
#define MENU_H

#include "Graph.h"
#include "algorithms/MST/Prim.h"
#include "algorithms/MST/Kruskal.h"
#include "algorithms/ShortestPath/Dijkstra.h"
#include "algorithms/ShortestPath/BellmanFord.h"
#include "algorithms/MaxFlow/FordFulkerson.h"
#include "Timer.h"

class Menu {
public:
    void displayMainMenu();
    void run();

private:
    Graph graph;

    void loadGraphFromFile();
    void generateRandomGraph();
    void displayGraph();
    void runMSTAlgorithms();
    void runShortestPathAlgorithms();
    void runMaxFlowAlgorithm();
    void runPerformanceTests();

    void displayPath(const std::vector<int>& dist, const std::vector<int>& parent, int start, int end) const;
    void displayMST(const std::vector<std::pair<int, int>>& mst) const;
};

#endif // MENU_H