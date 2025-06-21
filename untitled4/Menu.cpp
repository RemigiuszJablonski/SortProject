#include "menu.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <queue>

void Menu::displayMainMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Wczytaj graf z pliku\n";
    std::cout << "2. Wygeneruj losowy graf\n";
    std::cout << "3. Wyświetl graf\n";
    std::cout << "4. Minimalne drzewo rozpinające (MST)\n";
    std::cout << "5. Najkrótsza ścieżka (SP)\n";
    std::cout << "6. Maksymalny przepływ\n";
    std::cout << "7. Testy wydajnościowe\n";
    std::cout << "8. Wyjście\n";
    std::cout << "Wybierz opcję: ";
}

void Menu::run() {
    bool running = true;

    while (running) {
        displayMainMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: loadGraphFromFile(); break;
            case 2: generateRandomGraph(); break;
            case 3: displayGraph(); break;
            case 4: runMSTAlgorithms(); break;
            case 5: runShortestPathAlgorithms(); break;
            case 6: runMaxFlowAlgorithm(); break;
            case 7: runPerformanceTests(); break;
            case 8: running = false; break;
            default: std::cout << "Nieprawidłowy wybór.\n"; break;
        }
    }
}

void Menu::loadGraphFromFile() {
    std::string filename;
    std::cout << "Podaj nazwę pliku: ";
    std::cin >> filename;

    if (graph.loadFromFile(filename)) {
        std::cout << "Graf wczytany pomyślnie.\n";
    } else {
        std::cout << "Błąd podczas wczytywania pliku.\n";
    }
}

void Menu::generateRandomGraph() {
    int vertices;
    float density;
    bool directed;

    std::cout << "Podaj liczbę wierzchołków: ";
    std::cin >> vertices;

    std::cout << "Podaj gęstość (25, 50, 99): ";
    std::cin >> density;
    density /= 100.0f;

    std::cout << "Graf skierowany? (0 - nie, 1 - tak): ";
    std::cin >> directed;

    graph.generateRandom(vertices, density, directed);
    std::cout << "Graf wygenerowany pomyślnie.\n";
}

void Menu::displayGraph() {
    int repChoice;
    std::cout << "Wybierz reprezentację (1 - macierz, 2 - lista): ";
    std::cin >> repChoice;

    if (repChoice == 1) {
        graph.display(Graph::MATRIX);
    } else {
        graph.display(Graph::LIST);
    }
}

void Menu::runMSTAlgorithms() {
    int algChoice;
    std::cout << "Wybierz algorytm (1 - Prim, 2 - Kruskal): ";
    std::cin >> algChoice;

    Timer timer;
    std::vector<std::pair<int, int>> mst;

    if (algChoice == 1) {
        std::cout << "Algorytm Prima:\n";

        timer.start();
        mst = Prim::findMSTMatrix(graph);
        timer.stop();
        std::cout << "Macierzowa: " << timer.elapsedMilliseconds() << " ms\n";
        displayMST(mst);

        timer.start();
        mst = Prim::findMSTList(graph);
        timer.stop();
        std::cout << "Listowa: " << timer.elapsedMilliseconds() << " ms\n";
        displayMST(mst);
    } else {
        std::cout << "Algorytm Kruskala:\n";

        timer.start();
        mst = Kruskal::findMSTMatrix(graph);
        timer.stop();
        std::cout << "Macierzowa: " << timer.elapsedMilliseconds() << " ms\n";
        displayMST(mst);

        timer.start();
        mst = Kruskal::findMSTList(graph);
        timer.stop();
        std::cout << "Listowa: " << timer.elapsedMilliseconds() << " ms\n";
        displayMST(mst);
    }
}

void Menu::runShortestPathAlgorithms() {
    int algChoice, start, end;
    std::cout << "Wybierz algorytm (1 - Dijkstra, 2 - Ford-Bellman): ";
    std::cin >> algChoice;

    std::cout << "Podaj wierzchołek startowy: ";
    std::cin >> start;

    std::cout << "Podaj wierzchołek końcowy: ";
    std::cin >> end;

    Timer timer;
    std::pair<std::vector<int>, std::vector<int>> result;

    if (algChoice == 1) {
        std::cout << "Algorytm Dijkstry:\n";

        timer.start();
        result = Dijkstra::shortestPathMatrix(graph, start);
        timer.stop();
        std::cout << "Macierzowa: " << timer.elapsedMilliseconds() << " ms\n";
        displayPath(result.first, result.second, start, end);

        timer.start();
        result = Dijkstra::shortestPathList(graph, start);
        timer.stop();
        std::cout << "Listowa: " << timer.elapsedMilliseconds() << " ms\n";
        displayPath(result.first, result.second, start, end);
    } else {
        std::cout << "Algorytm Forda-Bellmana:\n";

        timer.start();
        result = BellmanFord::shortestPathMatrix(graph, start);
        timer.stop();
        std::cout << "Macierzowa: " << timer.elapsedMilliseconds() << " ms\n";
        if (result.first.empty()) {
            std::cout << "Graf zawiera cykl o ujemnej wadze.\n";
        } else {
            displayPath(result.first, result.second, start, end);
        }

        timer.start();
        result = BellmanFord::shortestPathList(graph, start);
        timer.stop();
        std::cout << "Listowa: " << timer.elapsedMilliseconds() << " ms\n";
        if (result.first.empty()) {
            std::cout << "Graf zawiera cykl o ujemnej wadze.\n";
        } else {
            displayPath(result.first, result.second, start, end);
        }
    }
}

void Menu::runMaxFlowAlgorithm() {
    int source, sink;
    std::cout << "Podaj źródło: ";
    std::cin >> source;

    std::cout << "Podaj ujście: ";
    std::cin >> sink;

    Timer timer;
    int maxFlow;

    std::cout << "Algorytm Forda-Fulkersona:\n";

    timer.start();
    maxFlow = FordFulkerson::maxFlowMatrix(graph, source, sink);
    timer.stop();
    std::cout << "Macierzowa: " << timer.elapsedMilliseconds() << " ms\n";
    std::cout << "Maksymalny przepływ: " << maxFlow << "\n";

    timer.start();
    maxFlow = FordFulkerson::maxFlowList(graph, source, sink);
    timer.stop();
    std::cout << "Listowa: " << timer.elapsedMilliseconds() << " ms\n";
    std::cout << "Maksymalny przepływ: " << maxFlow << "\n";
}

void Menu::runPerformanceTests() {
    std::vector<int> verticesSizes = {10, 20, 50, 100, 200, 500, 1000};
    std::vector<float> densities = {0.25f, 0.5f, 0.99f};
    int testIterations = 5;  // Zmniejszone dla szybkości testów

    std::cout << "Rozpoczęcie testów wydajnościowych...\n";

    // Testy dla MST
    std::cout << "\nTesty dla algorytmów MST:\n";
    for (int V : verticesSizes) {
        for (float density : densities) {
            double primMatrixTime = 0.0;
            double primListTime = 0.0;
            double kruskalMatrixTime = 0.0;
            double kruskalListTime = 0.0;

            for (int i = 0; i < testIterations; ++i) {
                Graph testGraph;
                testGraph.generateRandom(V, density, false);

                Timer timer;

                timer.start();
                Prim::findMSTMatrix(testGraph);
                timer.stop();
                primMatrixTime += timer.elapsedMilliseconds();

                timer.start();
                Prim::findMSTList(testGraph);
                timer.stop();
                primListTime += timer.elapsedMilliseconds();

                timer.start();
                Kruskal::findMSTMatrix(testGraph);
                timer.stop();
                kruskalMatrixTime += timer.elapsedMilliseconds();

                timer.start();
                Kruskal::findMSTList(testGraph);
                timer.stop();
                kruskalListTime += timer.elapsedMilliseconds();
            }

            primMatrixTime /= testIterations;
            primListTime /= testIterations;
            kruskalMatrixTime /= testIterations;
            kruskalListTime /= testIterations;

            std::cout << "V=" << V << ", density=" << (density*100) << "%:\n";
            std::cout << "  Prim (matrix): " << primMatrixTime << " ms\n";
            std::cout << "  Prim (list): " << primListTime << " ms\n";
            std::cout << "  Kruskal (matrix): " << kruskalMatrixTime << " ms\n";
            std::cout << "  Kruskal (list): " << kruskalListTime << " ms\n";
        }
    }

    // Testy dla najkrótszej ścieżki
    std::cout << "\nTesty dla algorytmów najkrótszej ścieżki:\n";
    for (int V : verticesSizes) {
        for (float density : densities) {
            double dijkstraMatrixTime = 0.0;
            double dijkstraListTime = 0.0;
            double bellmanMatrixTime = 0.0;
            double bellmanListTime = 0.0;

            for (int i = 0; i < testIterations; ++i) {
                Graph testGraph;
                testGraph.generateRandom(V, density, true);

                Timer timer;

                timer.start();
                Dijkstra::shortestPathMatrix(testGraph, 0);
                timer.stop();
                dijkstraMatrixTime += timer.elapsedMilliseconds();

                timer.start();
                Dijkstra::shortestPathList(testGraph, 0);
                timer.stop();
                dijkstraListTime += timer.elapsedMilliseconds();

                timer.start();
                BellmanFord::shortestPathMatrix(testGraph, 0);
                timer.stop();
                bellmanMatrixTime += timer.elapsedMilliseconds();

                timer.start();
                BellmanFord::shortestPathList(testGraph, 0);
                timer.stop();
                bellmanListTime += timer.elapsedMilliseconds();
            }

            dijkstraMatrixTime /= testIterations;
            dijkstraListTime /= testIterations;
            bellmanMatrixTime /= testIterations;
            bellmanListTime /= testIterations;

            std::cout << "V=" << V << ", density=" << (density*100) << "%:\n";
            std::cout << "  Dijkstra (matrix): " << dijkstraMatrixTime << " ms\n";
            std::cout << "  Dijkstra (list): " << dijkstraListTime << " ms\n";
            std::cout << "  Bellman-Ford (matrix): " << bellmanMatrixTime << " ms\n";
            std::cout << "  Bellman-Ford (list): " << bellmanListTime << " ms\n";
        }
    }

    // Testy dla maksymalnego przepływu (tylko dla mniejszych grafów)
    std::cout << "\nTesty dla algorytmu Forda-Fulkersona:\n";
    for (int V : {10, 20, 50}) {
        for (float density : densities) {
            double ffMatrixTime = 0.0;
            double ffListTime = 0.0;

            for (int i = 0; i < testIterations; ++i) {
                Graph testGraph;
                testGraph.generateRandom(V, density, true);

                Timer timer;

                timer.start();
                FordFulkerson::maxFlowMatrix(testGraph, 0, V-1);
                timer.stop();
                ffMatrixTime += timer.elapsedMilliseconds();

                timer.start();
                FordFulkerson::maxFlowList(testGraph, 0, V-1);
                timer.stop();
                ffListTime += timer.elapsedMilliseconds();
            }

            ffMatrixTime /= testIterations;
            ffListTime /= testIterations;

            std::cout << "V=" << V << ", density=" << (density*100) << "%:\n";
            std::cout << "  Ford-Fulkerson (matrix): " << ffMatrixTime << " ms\n";
            std::cout << "  Ford-Fulkerson (list): " << ffListTime << " ms\n";
        }
    }
}

void Menu::displayPath(const std::vector<int>& dist, const std::vector<int>& parent, int start, int end) const {
    if (dist[end] == std::numeric_limits<int>::max()) {
        std::cout << "Nie istnieje ścieżka z " << start << " do " << end << "\n";
        return;
    }

    std::cout << "Koszt ścieżki: " << dist[end] << "\n";
    std::cout << "Ścieżka: ";

    std::vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }

    for (int i = path.size() - 1; i >= 0; --i) {
        std::cout << path[i];
        if (i != 0) std::cout << " -> ";
    }
    std::cout << "\n";
}

void Menu::displayMST(const std::vector<std::pair<int, int>>& mst) const {
    std::cout << "Minimalne drzewo rozpinające:\n";
    for (const auto& edge : mst) {
        std::cout << edge.first << " - " << edge.second << "\n";
    }
}