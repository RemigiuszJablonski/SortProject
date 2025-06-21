#ifndef GRAPH_H
#define GRAPH_H

struct Pair {
    int first;
    int second;
};

class Graph {
public:
    enum RepresentationType { MATRIX, LIST };

    // ... (metody takie same jak wcześniej)

    // Zmienione typy zwracane:
    int** getMatrix() const;
    Pair** getAdjList() const;
    const int* getListSizes() const;

private:
    int vertexCount;
    int edgeCount;
    bool directed;
    int** adjacencyMatrix;  // Dwuwymiarowa tablica
    Pair** adjacencyList;   // Tablica list sąsiedztwa
    int* listSizes;         // Rozmiary poszczególnych list
};

#endif