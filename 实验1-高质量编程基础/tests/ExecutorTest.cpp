#include "Executor.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace {

struct TestCase {
    const char* name;
    void (*run)();
};

void ExpectPose(const adas::Pose& actual, const adas::Pose& expected,
                const char* test_name) {
    if (!(actual == expected)) {
        std::cerr << "[FAIL] " << test_name << ": expected ("
                  << expected.x << ", " << expected.y << ", "
                  << expected.heading << "), got (" << actual.x << ", "
                  << actual.y << ", " << actual.heading << ")\n";
        std::exit(EXIT_FAILURE);
    }
}

void ShouldReturnDefaultPoseWhenNoInitialPoseIsProvided() {
    std::unique_ptr<adas::Executor> executor(adas::Executor::NewExecutor());
    if (!executor) std::exit(EXIT_FAILURE);
    ExpectPose(executor->Query(), {0, 0, 'N'}, __func__);
}

void ShouldReturnInitialPoseWithoutCommands() {
    std::unique_ptr<adas::Executor> executor(
        adas::Executor::NewExecutor({3, -2, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    ExpectPose(executor->Query(), {3, -2, 'E'}, __func__);
}

void ShouldMoveOneStepInEachDirection() {
    const std::vector<adas::Pose> starts = {
        {0, 0, 'N'}, {0, 0, 'S'}, {0, 0, 'E'}, {0, 0, 'W'}};
    const std::vector<adas::Pose> expected = {
        {0, 1, 'N'}, {0, -1, 'S'}, {1, 0, 'E'}, {-1, 0, 'W'}};
    for (std::size_t index = 0; index < starts.size(); ++index) {
        std::unique_ptr<adas::Executor> executor(
            adas::Executor::NewExecutor(starts[index]));
        if (!executor) std::exit(EXIT_FAILURE);
        executor->Execute("M");
        ExpectPose(executor->Query(), expected[index], __func__);
    }
}

void ShouldTurnLeftAndRightWithoutMoving() {
    std::unique_ptr<adas::Executor> executor(
        adas::Executor::NewExecutor({4, 5, 'N'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("L");
    ExpectPose(executor->Query(), {4, 5, 'W'}, __func__);
    executor->Execute("R");
    ExpectPose(executor->Query(), {4, 5, 'N'}, __func__);
}

void ShouldExecuteASequenceOfCommands() {
    std::unique_ptr<adas::Executor> executor(
        adas::Executor::NewExecutor({0, 0, 'N'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("MLMMRM");
    ExpectPose(executor->Query(), {-2, 2, 'N'}, __func__);
}

void ShouldLeavePoseUnchangedForEmptyCommands() {
    std::unique_ptr<adas::Executor> executor(
        adas::Executor::NewExecutor({7, 8, 'S'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("");
    ExpectPose(executor->Query(), {7, 8, 'S'}, __func__);
}

}  // namespace

int main() {
    const TestCase tests[] = {
        {"default pose", ShouldReturnDefaultPoseWhenNoInitialPoseIsProvided},
        {"initial pose", ShouldReturnInitialPoseWithoutCommands},
        {"movement by heading", ShouldMoveOneStepInEachDirection},
        {"left and right turns", ShouldTurnLeftAndRightWithoutMoving},
        {"command sequence", ShouldExecuteASequenceOfCommands},
        {"empty command", ShouldLeavePoseUnchangedForEmptyCommands},
    };

    for (const TestCase& test : tests) {
        test.run();
        std::cout << "[PASS] " << test.name << '\n';
    }
    std::cout << "All " << sizeof(tests) / sizeof(tests[0])
              << " tests passed.\n";
}
