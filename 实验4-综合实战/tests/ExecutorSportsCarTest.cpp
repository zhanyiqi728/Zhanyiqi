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

// ---- M 指令：步长为普通车的两倍 ----

void ShouldSportsCarMoveTwoStepsForM() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("M");
    ExpectPose(executor->Query(), {2, 0, 'E'}, __func__);
}

void ShouldSportsCarMoveFourStepsForFastM() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("FM");
    ExpectPose(executor->Query(), {4, 0, 'E'}, __func__);
}

void ShouldSportsCarMoveBackTwoStepsForReverseM() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BM");
    ExpectPose(executor->Query(), {-2, 0, 'E'}, __func__);
}

void ShouldSportsCarMoveBackFourStepsForFastReverseM() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BFM");
    ExpectPose(executor->Query(), {-4, 0, 'E'}, __func__);
}

// ---- L 指令：先左转再移动 ----

void ShouldSportsCarTurnLeftThenForward() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("L");
    ExpectPose(executor->Query(), {0, 1, 'N'}, __func__);
}

void ShouldSportsCarForwardTurnLeftForward() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("FL");
    ExpectPose(executor->Query(), {1, 1, 'N'}, __func__);
}

void ShouldSportsCarTurnRightThenBackward() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BL");
    ExpectPose(executor->Query(), {0, 1, 'S'}, __func__);
}

void ShouldSportsCarBackwardTurnRightBackward() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BFL");
    ExpectPose(executor->Query(), {-1, 1, 'S'}, __func__);
}

// ---- R 指令：先右转再移动 ----

void ShouldSportsCarTurnRightThenForward() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("R");
    ExpectPose(executor->Query(), {0, -1, 'S'}, __func__);
}

void ShouldSportsCarForwardTurnRightForward() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("FR");
    ExpectPose(executor->Query(), {1, -1, 'S'}, __func__);
}

void ShouldSportsCarTurnLeftThenBackward() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BR");
    ExpectPose(executor->Query(), {0, -1, 'N'}, __func__);
}

void ShouldSportsCarBackwardTurnLeftBackward() {
    std::unique_ptr<Executor> executor(
        Executor::NewExecutor({0, 0, 'E'}, VehicleType::SportsCar));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BFR");
    ExpectPose(executor->Query(), {-1, -1, 'N'}, __func__);
}

}  // namespace

int main() {
    const std::vector<TestCase> tests = {
        {"should_sports_car_move_two_steps_for_M", ShouldSportsCarMoveTwoStepsForM},
        {"should_sports_car_move_four_steps_for_FM", ShouldSportsCarMoveFourStepsForFastM},
        {"should_sports_car_move_back_two_steps_for_BM", ShouldSportsCarMoveBackTwoStepsForReverseM},
        {"should_sports_car_move_back_four_steps_for_BFM", ShouldSportsCarMoveBackFourStepsForFastReverseM},
        {"should_sports_car_turn_left_then_forward_for_L", ShouldSportsCarTurnLeftThenForward},
        {"should_sports_car_forward_turn_left_forward_for_FL", ShouldSportsCarForwardTurnLeftForward},
        {"should_sports_car_turn_right_then_backward_for_BL", ShouldSportsCarTurnRightThenBackward},
        {"should_sports_car_backward_turn_right_backward_for_BFL", ShouldSportsCarBackwardTurnRightBackward},
        {"should_sports_car_turn_right_then_forward_for_R", ShouldSportsCarTurnRightThenForward},
        {"should_sports_car_forward_turn_right_forward_for_FR", ShouldSportsCarForwardTurnRightForward},
        {"should_sports_car_turn_left_then_backward_for_BR", ShouldSportsCarTurnLeftThenBackward},
        {"should_sports_car_backward_turn_left_backward_for_BFR", ShouldSportsCarBackwardTurnLeftBackward},
    };
    return Run(tests);
}
