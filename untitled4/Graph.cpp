#include "Graph.h"
#include <cstdio>
#include <cstdlib>
#include <cstring> // dla memset

// --- Pomocnicze funkcje ---
static int randInt(int min, int max) {
    return min + (rand() % (max - min + 1));
}

// --- Konstruktor/Destruktor ---
Graph::Graph() : vertexCount(0), edgeCount(0), directed(false),
                adjacencyMatrix(nullptr), adjacencyList(nullptr), listSizes(nullptr) {}

Graph::~Graph() {
    clear();
}

// --- Czyszczenie pamięci ---
void Graph::clear() {
    if (adjacencyMatrix) {
        for (int i = 0; i < vertexCount; ++i) {
            free(adjacencyMatrix[i]);
        }
        free(adjacencyMatrix);
        adjacencyMatrix = nullptr;
    }

    if (adjacencyList) {
        for (int i = 0; i < vertexCount; ++i) {
            free(adjacencyList[i]);
        }
        free(adjacencyList);
        adjacencyList = nullptr;
    }

    free(listSizes);
    listSizes = nullptr;

    vertexCount = 0;
    edgeCount = 0;
}

// --- Wczytywanie z pliku ---
bool Graph::loadFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return false;

    clear();
    fscanf(file, "%d %d", &edgeCount, &vertexCount);

    // Alokacja macierzy
    adjacencyMatrix = (int**)malloc(vertexCount * sizeof(int*));
    for (int i = 0; i < vertexCount; ++i) {
        adjacencyMatrix[i] = (int*)calloc(vertexCount, sizeof(int));
    }

    // Alokacja listy sąsiedztwa
    adjacencyList = (Pair**)malloc(vertexCount * sizeof(Pair*));
    listSizes = (int*)calloc(vertexCount, sizeof(int));

    // Wczytywanie krawędzi
    for (int i = 0; i < edgeCount; ++i) {
        int u, v, weight;
        fscanf(file, "%d %d %d", &u, &v, &weight);

        // Macierz sąsiedztwa
        adjacencyMatrix[u][v] = weight;
        if (!directed) adjacencyMatrix[v][u] = weight;

        // Lista sąsiedztwa
        adjacencyList[u] = (Pair*)realloc(adjacencyList[u], (listSizes[u] + 1) * sizeof(Pair));
        adjacencyList[u][listSizes[u]] = {v, weight};
        listSizes[u]++;

        if (!directed) {
            adjacencyList[v] = (Pair*)realloc(adjacencyList[v], (listSizes[v] + 1) * sizeof(Pair));
            adjacencyList[v][listSizes[v]] = {u, weight};
            listSizes[v]++;
        }
    }

    fclose(file);
    return true;
}

// --- Generowanie losowego grafu ---
void Graph::generateRandom(int vertices, float density, bool isDirected) {
    clear();
    vertexCount = vertices;
    directed = isDirected;

    // Alokacja macierzy
    adjacencyMatrix = (int**)malloc(vertexCount * sizeof(int*));
    for (int i = 0; i < vertexCount; ++i) {
        adjacencyMatrix[i] = (int*)calloc(vertexCount, sizeof(int));
    }

    // Alokacja listy sąsiedztwa
    adjacencyList = (Pair**)malloc(vertexCount * sizeof(Pair*));
    listSizes = (int*)calloc(vertexCount, sizeof(int));

    // Budowa drzewa rozpinającego
    for (int i = 1; i < vertexCount; ++i) {
        int j = rand() % i;
        int weight = randInt(1, 100);

        adjacencyMatrix[j][i] = weight;
        adjacencyList[j] = (Pair*)realloc(adjacencyList[j], (listSizes[j] + 1) * sizeof(Pair));
        adjacencyList[j][listSizes[j]++] = {i, weight};

        if (!directed) {
            adjacencyMatrix[i][j] = weight;
            adjacencyList[i] = (Pair*)realloc(adjacencyList[i], (listSizes[i] + 1) * sizeof(Pair));
            adjacencyList[i][listSizes[i]++] = {j, weight};
        }
        edgeCount++;
    }

    // Dodawanie losowych krawędzi
    int maxEdges = directed ? vertexCount * (vertexCount - 1)
                          : vertexCount * (vertexCount - 1) / 2;
    int targetEdges = (int)(density * maxEdges);

    while (edgeCount < targetEdges) {
        int u = rand() % vertexCount;
        int v = rand() % vertexCount;

        if (u != v && adjacencyMatrix[u][v] == 0) {
            int weight = randInt(1, 100);

            adjacencyMatrix[u][v] = weight;
            adjacencyList[u] = (Pair*)realloc(adjacencyList[u], (listSizes[u] + 1) * sizeof(Pair));
            adjacencyList[u][listSizes[u]++] = {v, weight};

            if (!directed) {
                adjacencyMatrix[v][u] = weight;
                adjacencyList[v] = (Pair*)realloc(adjacencyList[v], (listSizes[v] + 1) * sizeof(Pair));
                adjacencyList[v][listSizes[v]++] = {u, weight};
            }
            edgeCount++;
        }
    }
}

// --- Wyświetlanie grafu ---
void Graph::display(RepresentationType type) const {
    if (type == MATRIX) {
        printf("Macierz incydencji (%d x %d):\n", vertexCount, vertexCount);
        for (int i = 0; i < vertexCount; ++i) {
            for (int j = 0; j < vertexCount; ++j) {
                printf("%3d ", adjacencyMatrix[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Lista następników (|V| = %d):\n", vertexCount);
        for (int i = 0; i < vertexCount; ++i) {
            printf("%2d: ", i);
            for (int j = 0; j < listSizes[i]; ++j) {
                printf("(%d, %d) ", adjacencyList[i][j].first, adjacencyList[i][j].second);
            }
            printf("\n");
        }
    }
}

// --- Konwersje między reprezentacjami ---
void Graph::convertToMatrix() {
    if (adjacencyMatrix) return;

    // Alokacja macierzy
    adjacencyMatrix = (int**)malloc(vertexCount * sizeof(int*));
    for (int i = 0; i < vertexCount; ++i) {
        adjacencyMatrix[i] = (int*)calloc(vertexCount, sizeof(int));
    }

    // Wypełnianie macierzy z listy
    for (int u = 0; u < vertexCount; ++u) {
        for (int j = 0; j < listSizes[u]; ++j) {
            int v = adjacencyList[u][j].first;
            adjacencyMatrix[u][v] = adjacencyList[u][j].second;
        }
    }
}

void Graph::convertToList() {
    if (adjacencyList) return;

    // Alokacja listy
    adjacencyList = (Pair**)malloc(vertexCount * sizeof(Pair*));
    listSizes = (int*)calloc(vertexCount, sizeof(int));

    // Wypełnianie listy z macierzy
    for (int u = 0; u < vertexCount; ++u) {
        for (int v = 0; v < vertexCount; ++v) {
            if (adjacencyMatrix[u][v] != 0) {
                adjacencyList[u] = (Pair*)realloc(adjacencyList[u], (listSizes[u] + 1) * sizeof(Pair));
                adjacencyList[u][listSizes[u]++] = {v, adjacencyMatrix[u][v]};
            }
        }
    }
}

// --- Gettery ---
int Graph::getVertexCount() const { return vertexCount; }
int Graph::getEdgeCount() const { return edgeCount; }
bool Graph::isDirected() const { return directed; }

// --- Dostęp do struktur danych ---
int** Graph::getMatrix() const { return adjacencyMatrix; }
Pair** Graph::getAdjList() const { return adjacencyList; }
const int* Graph::getListSizes() const { return listSizes; }