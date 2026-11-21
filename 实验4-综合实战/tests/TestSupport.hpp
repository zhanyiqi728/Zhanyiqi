#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>

#include "Executor.hpp"

namespace adas::test {

struct TestCase {
    const char* name;
    void (*run)();
};

inline void ExpectPose(const adas::Pose& actual, const adas::Pose& expected,
                       const char* test_name) {
    if (!(actual == expected)) {
        std::cerr << "[FAIL] " << test_name << ": expected ("
                  << expected.x << ", " << expected.y << ", "
                  << expected.heading << "), got (" << actual.x << ", "
                  << actual.y << ", " << actual.heading << ")\n";
        std::exit(EXIT_FAILURE);
    }
}

inline int Run(const std::vector<TestCase>& tests) {
    for (const TestCase& test : tests) {
        test.run();
        std::cout << "[PASS] " << test.name << '\n';
    }
    std::cout << "All " << tests.size() << " tests passed.\n";
    return EXIT_SUCCESS;
}

}  // namespace adas::test
