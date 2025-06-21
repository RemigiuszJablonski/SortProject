cmake_minimum_required(VERSION 3.30)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 main.cpp
        headers/Menu.h
        headers/graphs/Graph.h
        headers/graphs/MatrixGraph.h
        headers/graphs/ListGraph.h
        headers/algorithms/MST_Prim.h
        headers/algorithms/MST_Kruskal.h
        headers/algorithms/SP_Dijkstra.h
        headers/algorithms/SP_BellmanFord.h
        headers/utils/GraphGenerator.h
        headers/utils/PerformanceTester.h
        headers/utils/FileHandler.h
        headers/utils/Timer.h
        source/graphs/MatrixGraph.cpp
        source/graphs/ListGraph.cpp
        source/algorithms/MST_Prim.cpp
        source/algorithms/MST_Kruskal.cpp
        source/algorithms/SP_Dijkstra.cpp
        source/algorithms/SP_BellmanFord.cpp
        source/utils/GraphGenerator.cpp
        source/utils/PerformanceTester.cpp
        source/utils/FileHandler.cpp
        source/utils/Menu.cpp
        source/utils/GraphValidator.cpp
)
