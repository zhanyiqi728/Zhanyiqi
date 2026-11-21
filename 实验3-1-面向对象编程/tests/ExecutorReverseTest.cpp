#include <cstdlib>
#include <memory>
#include <vector>

#include "Executor.hpp"
#include "TestSupport.hpp"

namespace {

using adas::Executor;
using adas::Pose;
using adas::test::ExpectPose;
using adas::test::Run;
using adas::test::TestCase;

// 倒车状态下 M 后退 1 格。
void ShouldReturnXMinus1GivenBMAndFacingEast() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BM");
    ExpectPose(executor->Query(), {-1, 0, 'E'}, __func__);
}

// 加速 + 倒车叠加，M 后退 2 格。
void ShouldReturnXMinus2GivenBFMAndFacingEast() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BFM");
    ExpectPose(executor->Query(), {-2, 0, 'E'}, __func__);
}

// 再次收到 B，倒车状态取消，M 恢复前进 1 格。
void ShouldReturnYPlus1GivenBBMAndFacingNorth() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BBM");
    ExpectPose(executor->Query(), {0, 1, 'N'}, __func__);
}

// 倒车状态下 L 变成右转。
void ShouldReturnFacingSGivenBLAndFacingEast() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BL");
    ExpectPose(executor->Query(), {0, 0, 'S'}, __func__);
}

// 加速 + 倒车叠加，L 先后退 1 格再右转。
void ShouldReturnSAndXMinus1GivenBFLAndFacingEast() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BFL");
    ExpectPose(executor->Query(), {-1, 0, 'S'}, __func__);
}

// 倒车状态下 R 变成左转。
void ShouldReturnFacingNGivenBRAndFacingEast() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BR");
    ExpectPose(executor->Query(), {0, 0, 'N'}, __func__);
}

// 加速 + 倒车叠加，R 先后退 1 格再左转。
void ShouldReturnNAndXMinus1GivenBFRAndFacingEast() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BFR");
    ExpectPose(executor->Query(), {-1, 0, 'N'}, __func__);
}

}  // namespace

int main() {
    const std::vector<TestCase> tests = {
        {"should_return_x_minus_1_given_command_is_BM_and_facing_is_E",
         ShouldReturnXMinus1GivenBMAndFacingEast},
        {"should_return_x_minus_2_given_command_is_BFM_and_facing_is_E",
         ShouldReturnXMinus2GivenBFMAndFacingEast},
        {"should_return_y_plus_1_given_command_is_BBM_and_facing_is_N",
         ShouldReturnYPlus1GivenBBMAndFacingNorth},
        {"should_return_facing_S_given_command_is_BL_and_facing_is_E",
         ShouldReturnFacingSGivenBLAndFacingEast},
        {"should_return_S_and_x_minus_1_given_command_is_BFL_and_facing_is_E",
         ShouldReturnSAndXMinus1GivenBFLAndFacingEast},
        {"should_return_facing_N_given_command_is_BR_and_facing_is_E",
         ShouldReturnFacingNGivenBRAndFacingEast},
        {"should_return_N_and_x_minus_1_given_command_is_BFR_and_facing_is_E",
         ShouldReturnNAndXMinus1GivenBFRAndFacingEast},
    };
    return Run(tests);
}
