#include <cstdlib>
#include <memory>
#include <vector>

#include "Executor.hpp"
#include "TestSupport.hpp"

namespace {

using adas::Executor;
using adas::Pose;
using adas::VehicleType;
using adas::test::ExpectPose;
using adas::test::Run;
using adas::test::TestCase;

// ---- M 指令：前进/后退，加速翻倍 ----

void ShouldBusMoveOneStepForM() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("M");
    ExpectPose(executor->Query(), {1, 0, 'E'}, __func__);
}

void ShouldBusMoveTwoStepsForFastM() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("FM");
    ExpectPose(executor->Query(), {2, 0, 'E'}, __func__);
}

void ShouldBusMoveBackOneStepForReverseM() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BM");
    ExpectPose(executor->Query(), {-1, 0, 'E'}, __func__);
}

void ShouldBusMoveBackTwoStepsForFastReverseM() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BFM");
    ExpectPose(executor->Query(), {-2, 0, 'E'}, __func__);
}

// ---- L 指令：先移动再左转 ----

void ShouldBusMoveForwardThenTurnLeft() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("L");
    ExpectPose(executor->Query(), {1, 0, 'N'}, __func__);
}

void ShouldBusMoveForwardTwiceThenTurnLeft() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("FL");
    ExpectPose(executor->Query(), {2, 0, 'N'}, __func__);
}

void ShouldBusMoveBackThenTurnRight() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BL");
    ExpectPose(executor->Query(), {-1, 0, 'S'}, __func__);
}

void ShouldBusMoveBackTwiceThenTurnRight() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BFL");
    ExpectPose(executor->Query(), {-2, 0, 'S'}, __func__);
}

// ---- R 指令：先移动再右转 ----

void ShouldBusMoveForwardThenTurnRight() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("R");
    ExpectPose(executor->Query(), {1, 0, 'S'}, __func__);
}

void ShouldBusMoveForwardTwiceThenTurnRight() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("FR");
    ExpectPose(executor->Query(), {2, 0, 'S'}, __func__);
}

void ShouldBusMoveBackThenTurnLeft() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BR");
    ExpectPose(executor->Query(), {-1, 0, 'N'}, __func__);
}

void ShouldBusMoveBackTwiceThenTurnLeft() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::Bus));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BFR");
    ExpectPose(executor->Query(), {-2, 0, 'N'}, __func__);
}

}  // namespace

int main() {
    const std::vector<TestCase> tests = {
        {"should_bus_move_one_step_for_M", ShouldBusMoveOneStepForM},
        {"should_bus_move_two_steps_for_FM", ShouldBusMoveTwoStepsForFastM},
        {"should_bus_move_back_one_step_for_BM", ShouldBusMoveBackOneStepForReverseM},
        {"should_bus_move_back_two_steps_for_BFM", ShouldBusMoveBackTwoStepsForFastReverseM},
        {"should_bus_move_forward_then_turn_left_for_L", ShouldBusMoveForwardThenTurnLeft},
        {"should_bus_move_forward_twice_then_turn_left_for_FL", ShouldBusMoveForwardTwiceThenTurnLeft},
        {"should_bus_move_back_then_turn_right_for_BL", ShouldBusMoveBackThenTurnRight},
        {"should_bus_move_back_twice_then_turn_right_for_BFL", ShouldBusMoveBackTwiceThenTurnRight},
        {"should_bus_move_forward_then_turn_right_for_R", ShouldBusMoveForwardThenTurnRight},
        {"should_bus_move_forward_twice_then_turn_right_for_FR", ShouldBusMoveForwardTwiceThenTurnRight},
        {"should_bus_move_back_then_turn_left_for_BR", ShouldBusMoveBackThenTurnLeft},
        {"should_bus_move_back_twice_then_turn_left_for_BFR", ShouldBusMoveBackTwiceThenTurnLeft},
    };
    return Run(tests);
}
