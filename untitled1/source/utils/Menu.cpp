#include "../../include/Menu.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Menu::loadGraph() {
    std::string filename;
    std::cout << "Enter filename (from data/input/): ";
    std::cin >> filename;
    try {
        currentGraph.reset(FileHandler::loadGraphFromFile("data/input/" + filename, isDirected));
        std::cout << "Graph loaded successfully\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void Menu::generateGraph() {
    int vertices, density;
    std::cout << "Enter number of vertices and density (25/50/99): ";
    std::cin >> vertices >> density;
    currentGraph.reset(GraphGenerator::generateGraph(vertices, density, isDirected));
    std::cout << "Graph generated\n";
}

void Menu::runAlgorithm(const std::string& algorithm) {
    if (!currentGraph) {
        std::cout << "No graph loaded\n";
        return;
    }

    if (algorithm == "Prim") {
        MST_Prim prim;
        auto mst = prim.findMST(*currentGraph);
        std::cout << "MST edges:\n";
        for (const Edge& edge : mst) {
            std::cout << edge.from << " - " << edge.to << " (" << edge.weight << ")\n";
        }
    }
    else if (algorithm == "Dijkstra") {
        int source;
        std::cout << "Enter source vertex: ";
        std::cin >> source;
        SP_Dijkstra dijkstra;
        auto distances = dijkstra.findShortestPath(*currentGraph, source);
        for (int i = 0; i < distances.size(); ++i) {
            std::cout << "Distance to " << i << ": " << distances[i] << "\n";
        }
    }
    // ... inne algorytmy
}

void Menu::readConfig() {
    std::ifstream config("config.txt");
    if (config.is_open()) {
        std::string line;
        while (std::getline(config, line)) {
            if (line.find("directed=") != std::string::npos) {
                isDirected = (line.substr(9) == "true");
            }
        }
    }
}