#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "../graphs/Graph.h"
#include <memory>
#include <string>

class FileHandler {
public:
    static std::unique_ptr<Graph> loadGraphFromFile(const std::string& filename, bool directed, bool matrixRepresentation);
    static void saveGraphToFile(const Graph& graph, const std::string& filename);
};

#endif // FILE_HANDLER_H