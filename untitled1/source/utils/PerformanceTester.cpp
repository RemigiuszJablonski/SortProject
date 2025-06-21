#include "../../headers/utils/PerformanceTester.h"
#include <chrono>
#include <fstream>

void PerformanceTester::testAlgorithm(AlgorithmFunc algorithm, const Graph& graph, int iterations) {
    double total_time = 0;
    for (int i = 0; i < iterations; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        algorithm(graph);
        auto end = std::chrono::high_resolution_clock::now();
        total_time += std::chrono::duration<double, std::milli>(end - start).count();
    }
    double avg_time = total_time / iterations;
    std::cout << "Average time: " << avg_time << " ms\n";
}

void PerformanceTester::saveResultsToCSV(const std::string& filename, const std::vector<TestResult>& results) {
    std::ofstream file(filename);
    file << "Vertices,Density,Time(ms)\n";
    for (const auto& result : results) {
        file << result.vertices << "," << result.density << "," << result.time << "\n";
    }
}