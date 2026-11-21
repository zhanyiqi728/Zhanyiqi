#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include "Executor.hpp"
#include "TestSupport.hpp"

namespace {

using adas::Executor;
using adas::Pose;
using adas::test::ExpectPose;
using adas::test::Run;
using adas::test::TestCase;

void ShouldReturnDefaultPoseWhenNoInitialPoseIsProvided() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    if (!executor) std::exit(EXIT_FAILURE);
    ExpectPose(executor->Query(), {0, 0, 'N'}, __func__);
}

void ShouldReturnInitialPoseWithoutCommands() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({3, -2, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    ExpectPose(executor->Query(), {3, -2, 'E'}, __func__);
}

void ShouldMoveOneStepInEachDirection() {
    const std::vector<Pose> starts = {
        {0, 0, 'N'}, {0, 0, 'S'}, {0, 0, 'E'}, {0, 0, 'W'}};
    const std::vector<Pose> expected = {
        {0, 1, 'N'}, {0, -1, 'S'}, {1, 0, 'E'}, {-1, 0, 'W'}};
    for (std::size_t index = 0; index < starts.size(); ++index) {
        std::unique_ptr<Executor> executor(
            Executor::NewExecutor(starts[index]));
        if (!executor) std::exit(EXIT_FAILURE);
        executor->Execute("M");
        ExpectPose(executor->Query(), expected[index], __func__);
    }
}

void ShouldTurnLeftAndRightWithoutMoving() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({4, 5, 'N'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("L");
    ExpectPose(executor->Query(), {4, 5, 'W'}, __func__);
    executor->Execute("R");
    ExpectPose(executor->Query(), {4, 5, 'N'}, __func__);
}

void ShouldExecuteASequenceOfCommands() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'N'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("MLMMRM");
    ExpectPose(executor->Query(), {-2, 2, 'N'}, __func__);
}

void ShouldLeavePoseUnchangedForEmptyCommands() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({7, 8, 'S'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("");
    ExpectPose(executor->Query(), {7, 8, 'S'}, __func__);
}

}  // namespace

int main() {
    const std::vector<TestCase> tests = {
        {"default pose", ShouldReturnDefaultPoseWhenNoInitialPoseIsProvided},
        {"initial pose", ShouldReturnInitialPoseWithoutCommands},
        {"movement by heading", ShouldMoveOneStepInEachDirection},
        {"left and right turns", ShouldTurnLeftAndRightWithoutMoving},
        {"command sequence", ShouldExecuteASequenceOfCommands},
        {"empty command", ShouldLeavePoseUnchangedForEmptyCommands},
    };
    return Run(tests);
}
