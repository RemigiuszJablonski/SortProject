cmake_minimum_required(VERSION 3.20)
project(untitled4)

set(CMAKE_CXX_STANDARD 17)

# Główne pliki źródłowe
set(MAIN_SOURCES
        main.cpp
        Graph.cpp
        Menu.cpp
)

# Pliki algorytmów
set(ALGORITHM_SOURCES
        algorithms/MST/Prim.cpp
        algorithms/MST/Kruskal.cpp
        algorithms/ShortestPath/Dijkstra.cpp
        algorithms/ShortestPath/BellmanFord.cpp
        algorithms/MaxFlow/FordFulkerson.cpp
)

# Łączna lista plików źródłowych
add_executable(untitled4
        ${MAIN_SOURCES}
        ${ALGORITHM_SOURCES}
)

# Ścieżki do nagłówków
target_include_directories(untitled4 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/MST
        ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/ShortestPath
        ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/MaxFlow
)