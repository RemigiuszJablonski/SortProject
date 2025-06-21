#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <limits>
#include <random>
#include <string>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct Edge {
    int src, dest, weight;

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;
    vector<vector<pair<int, int>>> adjList;
    vector<Edge> edges;

public:
    Graph(int vertices) : V(vertices) {
        adjMatrix.resize(V, vector<int>(V, 0));
        adjList.resize(V);
    }

    void addEdge(int src, int dest, int weight) {
        // Dla reprezentacji macierzowej
        adjMatrix[src][dest] = weight;
        adjMatrix[dest][src] = weight; // dla grafu nieskierowanego

        // Dla reprezentacji listowej
        adjList[src].emplace_back(dest, weight);
        adjList[dest].emplace_back(src, weight); // dla grafu nieskierowanego

        // Zapisz krawędź do listy krawędzi
        edges.push_back({src, dest, weight});
    }

    int getV() const { return V; }
    const vector<vector<int>>& getAdjMatrix() const { return adjMatrix; }
    const vector<vector<pair<int, int>>>& getAdjList() const { return adjList; }
    const vector<Edge>& getEdges() const { return edges; }

    void generateRandomGraph(int density) {
        // Wyczyść istniejące krawędzie
        adjMatrix = vector<vector<int>>(V, vector<int>(V, 0));
        adjList = vector<vector<pair<int, int>>>(V);
        edges.clear();

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> weight_dist(1, 100);

        // Najpierw utwórz drzewo rozpinające aby zapewnić spójność
        for (int i = 1; i < V; ++i) {
            int weight = weight_dist(gen);
            int parent = uniform_int_distribution<>(0, i-1)(gen);
            addEdge(parent, i, weight);
        }

        // Oblicz maksymalną liczbę krawędzi i docelową liczbę krawędzi
        int max_edges = V * (V - 1) / 2;
        int target_edges = (max_edges * density) / 100;

        // Dodaj dodatkowe krawędzie do osiągnięcia żądanej gęstości
        while (edges.size() < target_edges) {
            int u = uniform_int_distribution<>(0, V-1)(gen);
            int v = uniform_int_distribution<>(0, V-1)(gen);
            if (u != v && adjMatrix[u][v] == 0) {
                int weight = weight_dist(gen);
                addEdge(u, v, weight);
            }
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Nie można otworzyć pliku: " << filename << endl;
            return;
        }

        int E;
        file >> E >> V;

        adjMatrix = vector<vector<int>>(V, vector<int>(V, 0));
        adjList = vector<vector<pair<int, int>>>(V);
        edges.clear();

        for (int i = 0; i < E; ++i) {
            int src, dest, weight;
            file >> src >> dest >> weight;
            addEdge(src, dest, weight);
        }

        file.close();
    }

    void printMatrixRepresentation() {
        cout << "Reprezentacja macierzowa:\n";
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                cout << setw(4) << adjMatrix[i][j];
            }
            cout << endl;
        }
    }

    void printListRepresentation() {
        cout << "Reprezentacja listowa:\n";
        for (int i = 0; i < V; ++i) {
            cout << i << ": ";
            for (const auto& neighbor : adjList[i]) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

// Algorytm Prima dla reprezentacji macierzowej
vector<Edge> primMatrix(const Graph& graph) {
    int V = graph.getV();
    const auto& adjMatrix = graph.getAdjMatrix();
    vector<Edge> mst;
    vector<bool> inMST(V, false);
    vector<int> key(V, numeric_limits<int>::max());
    vector<int> parent(V, -1);

    key[0] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        for (int v = 0; v < V; ++v) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        inMST[u] = true;

        for (int v = 0; v < V; ++v) {
            if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = adjMatrix[u][v];
            }
        }
    }

    for (int i = 1; i < V; ++i) {
        mst.push_back({parent[i], i, key[i]});
    }

    return mst;
}

// Algorytm Prima dla reprezentacji listowej
vector<Edge> primList(const Graph& graph) {
    int V = graph.getV();
    const auto& adjList = graph.getAdjList();
    vector<Edge> mst;
    vector<bool> inMST(V, false);
    vector<int> key(V, numeric_limits<int>::max());
    vector<int> parent(V, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, 0});
    key[0] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (const auto& neighbor : adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    for (int i = 1; i < V; ++i) {
        mst.push_back({parent[i], i, key[i]});
    }

    return mst;
}

// Funkcja pomocnicza do znajdowania rodzica w zbiorze dla Kruskala
int findParent(vector<int>& parent, int i) {
    if (parent[i] != i) {
        parent[i] = findParent(parent, parent[i]);
    }
    return parent[i];
}

// Algorytm Kruskala dla reprezentacji macierzowej/listowej (używa listy krawędzi)
vector<Edge> kruskal(const Graph& graph) {
    int V = graph.getV();
    vector<Edge> mst;
    vector<Edge> edges = graph.getEdges();
    sort(edges.begin(), edges.end());

    vector<int> parent(V);
    for (int i = 0; i < V; ++i) {
        parent[i] = i;
    }

    int edgeCount = 0;
    for (const auto& edge : edges) {
        int uRoot = findParent(parent, edge.src);
        int vRoot = findParent(parent, edge.dest);

        if (uRoot != vRoot) {
            mst.push_back(edge);
            parent[vRoot] = uRoot;
            if (++edgeCount == V - 1) {
                break;
            }
        }
    }

    return mst;
}

// Algorytm Dijkstry dla reprezentacji macierzowej
vector<int> dijkstraMatrix(const Graph& graph, int src) {
    int V = graph.getV();
    const auto& adjMatrix = graph.getAdjMatrix();
    vector<int> dist(V, numeric_limits<int>::max());
    vector<bool> visited(V, false);

    dist[src] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        if (dist[u] == numeric_limits<int>::max()) {
            break;
        }

        visited[u] = true;

        for (int v = 0; v < V; ++v) {
            if (adjMatrix[u][v] && !visited[v] && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
            }
        }
    }

    return dist;
}

// Algorytm Dijkstry dla reprezentacji listowej
vector<int> dijkstraList(const Graph& graph, int src) {
    int V = graph.getV();
    const auto& adjList = graph.getAdjList();
    vector<int> dist(V, numeric_limits<int>::max());
    vector<bool> visited(V, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const auto& neighbor : adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

// Algorytm Forda-Bellmana dla reprezentacji listowej
vector<int> bellmanFordList(const Graph& graph, int src) {
    int V = graph.getV();
    const auto& edges = graph.getEdges();
    vector<int> dist(V, numeric_limits<int>::max());
    dist[src] = 0;

    for (int i = 1; i < V; ++i) {
        for (const auto& edge : edges) {
            if (dist[edge.src] != numeric_limits<int>::max() &&
                dist[edge.src] + edge.weight < dist[edge.dest]) {
                dist[edge.dest] = dist[edge.src] + edge.weight;
            }
        }
    }

    // Sprawdzenie ujemnych cykli
    for (const auto& edge : edges) {
        if (dist[edge.src] != numeric_limits<int>::max() &&
            dist[edge.src] + edge.weight < dist[edge.dest]) {
            cerr << "Graf zawiera ujemny cykl!" << endl;
            return {};
        }
    }

    return dist;
}

void printMST(const vector<Edge>& mst) {
    cout << "Minimalne drzewo rozpinajace:\n";
    int totalWeight = 0;
    for (const auto& edge : mst) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    cout << "Calkowita waga MST: " << totalWeight << endl;
}

void printShortestPaths(const vector<int>& dist, int src) {
    cout << "Najkrotsze sciezki z wierzcholka " << src << ":\n";
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i] == numeric_limits<int>::max()) {
            cout << i << ": nieosiagalny" << endl;
        } else {
            cout << i << ": " << dist[i] << endl;
        }
    }
}

void runPerformanceTests() {
    vector<int> sizes = {10, 20, 50, 100, 200, 500, 1000};
    vector<int> densities = {25, 50, 99};

    cout << "Badanie wydajnosci algorytmow:\n";
    cout << "Rozmiar\tGestosc\tPrimMatrix\tPrimList\tKruskal\tDijkstraMatrix\tDijkstraList\tBellmanFord\n";

    for (int size : sizes) {
        for (int density : densities) {
            Graph g(size);
            g.generateRandomGraph(density);

            cout << size << "\t" << density << "\t";

            // Pomiar czasu dla Prima (macierz)
            auto start = high_resolution_clock::now();
            auto mst1 = primMatrix(g);
            auto stop = high_resolution_clock::now();
            cout << duration_cast<microseconds>(stop - start).count() << "\t";

            // Pomiar czasu dla Prima (lista)
            start = high_resolution_clock::now();
            auto mst2 = primList(g);
            stop = high_resolution_clock::now();
            cout << duration_cast<microseconds>(stop - start).count() << "\t";

            // Pomiar czasu dla Kruskala
            start = high_resolution_clock::now();
            auto mst3 = kruskal(g);
            stop = high_resolution_clock::now();
            cout << duration_cast<microseconds>(stop - start).count() << "\t";

            // Pomiar czasu dla Dijkstry (macierz)
            start = high_resolution_clock::now();
            auto dist1 = dijkstraMatrix(g, 0);
            stop = high_resolution_clock::now();
            cout << duration_cast<microseconds>(stop - start).count() << "\t";

            // Pomiar czasu dla Dijkstry (lista)
            start = high_resolution_clock::now();
            auto dist2 = dijkstraList(g, 0);
            stop = high_resolution_clock::now();
            cout << duration_cast<microseconds>(stop - start).count() << "\t";

            // Pomiar czasu dla Bellmana-Forda
            start = high_resolution_clock::now();
            auto dist3 = bellmanFordList(g, 0);
            stop = high_resolution_clock::now();
            cout << duration_cast<microseconds>(stop - start).count() << endl;
        }
    }
}

void interactiveMode() {
    Graph g(1); // Tymczasowy graf z 1 wierzchołkiem
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Wczytaj graf z pliku\n";
        cout << "2. Wygeneruj losowy graf\n";
        cout << "3. Wyswietl reprezentacje grafu\n";
        cout << "4. Znajdz MST (Prim - macierz)\n";
        cout << "5. Znajdz MST (Prim - lista)\n";
        cout << "6. Znajdz MST (Kruskal)\n";
        cout << "7. Znajdz najkrotsze sciezki (Dijkstra - macierz)\n";
        cout << "8. Znajdz najkrotsze sciezki (Dijkstra - lista)\n";
        cout << "9. Znajdz najkrotsze sciezki (Bellman-Ford)\n";
        cout << "10. Przeprowadz testy wydajnosci\n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string filename;
                cout << "Podaj nazwe pliku: ";
                cin >> filename;
                g.loadFromFile(filename);
                break;
            }
            case 2: {
                int vertices, density;
                cout << "Podaj liczbe wierzcholkow: ";
                cin >> vertices;
                cout << "Podaj gestosc (25, 50, 99): ";
                cin >> density;
                g = Graph(vertices);
                g.generateRandomGraph(density);
                break;
            }
            case 3: {
                g.printMatrixRepresentation();
                cout << endl;
                g.printListRepresentation();
                break;
            }
            case 4: {
                auto start = high_resolution_clock::now();
                auto mst = primMatrix(g);
                auto stop = high_resolution_clock::now();
                printMST(mst);
                cout << "Czas wykonania: " << duration_cast<microseconds>(stop - start).count() << " μs\n";
                break;
            }
            case 5: {
                auto start = high_resolution_clock::now();
                auto mst = primList(g);
                auto stop = high_resolution_clock::now();
                printMST(mst);
                cout << "Czas wykonania: " << duration_cast<microseconds>(stop - start).count() << " μs\n";
                break;
            }
            case 6: {
                auto start = high_resolution_clock::now();
                auto mst = kruskal(g);
                auto stop = high_resolution_clock::now();
                printMST(mst);
                cout << "Czas wykonania: " << duration_cast<microseconds>(stop - start).count() << " μs\n";
                break;
            }
            case 7: {
                int src;
                cout << "Podaj wierzcholek startowy: ";
                cin >> src;
                auto start = high_resolution_clock::now();
                auto dist = dijkstraMatrix(g, src);
                auto stop = high_resolution_clock::now();
                printShortestPaths(dist, src);
                cout << "Czas wykonania: " << duration_cast<microseconds>(stop - start).count() << " μs\n";
                break;
            }
            case 8: {
                int src;
                cout << "Podaj wierzcholek startowy: ";
                cin >> src;
                auto start = high_resolution_clock::now();
                auto dist = dijkstraList(g, src);
                auto stop = high_resolution_clock::now();
                printShortestPaths(dist, src);
                cout << "Czas wykonania: " << duration_cast<microseconds>(stop - start).count() << " μs\n";
                break;
            }
            case 9: {
                int src;
                cout << "Podaj wierzcholek startowy: ";
                cin >> src;
                auto start = high_resolution_clock::now();
                auto dist = bellmanFordList(g, src);
                auto stop = high_resolution_clock::now();
                if (!dist.empty()) {
                    printShortestPaths(dist, src);
                }
                cout << "Czas wykonania: " << duration_cast<microseconds>(stop - start).count() << " μs\n";
                break;
            }
            case 10: {
                runPerformanceTests();
                break;
            }
            case 0: {
                cout << "Koniec programu.\n";
                break;
            }
            default: {
                cout << "Nieprawidlowy wybor.\n";
                break;
            }
        }
    } while (choice != 0);
}

int main() {
    interactiveMode();
    return 0;
}