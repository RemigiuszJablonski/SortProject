#ifndef MENU_H
#define MENU_H

#include <string>
#include <memory>
#include "../graphs/Graph.h"

class Menu {
    std::unique_ptr<Graph> currentGraph;

public:
    void mainLoop();
    void loadConfig(const std::string& configFile);

private:
    void displayMenu() const;
    void handleInput();
    void runSelectedAlgorithm() const;
    void generateRandomGraph();
    void loadGraphFromFile();
    void displayGraph() const;
};

#endif // MENU_H