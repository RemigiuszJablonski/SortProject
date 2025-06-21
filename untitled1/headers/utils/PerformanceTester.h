#ifndef PERFORMANCE_TESTER_H
#define PERFORMANCE_TESTER_H

#include <string>
#include <vector>

class PerformanceTester {
public:
    struct TestResult {
        int vertexCount;
        float density;
        double primTime;
        double kruskalTime;
        double dijkstraTime;
        double bellmanFordTime;
    };

    static std::vector<TestResult> runAllTests();
    static void saveResultsToFile(const std::vector<TestResult>& results, const std::string& filename);
};

#endif // PERFORMANCE_TESTER_H