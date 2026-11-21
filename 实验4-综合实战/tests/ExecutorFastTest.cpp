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

void ShouldReturnXPlus2GivenFastAndMAndFacingEast() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("FM");
    ExpectPose(executor->Query(), {2, 0, 'E'}, __func__);
}

void ShouldReturnNorthAndXPlus1GivenFastAndLAndFacingEast() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("FL");
    ExpectPose(executor->Query(), {1, 0, 'N'}, __func__);
}

void ShouldReturnSouthAndXPlus1GivenFastAndRAndFacingEast() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("FR");
    ExpectPose(executor->Query(), {1, 0, 'S'}, __func__);
}

void ShouldReturnYPlus1GivenCommandIsFFMAndFacingNorth() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor());
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("FFM");
    ExpectPose(executor->Query(), {0, 1, 'N'}, __func__);
}

}  // namespace

int main() {
    const std::vector<TestCase> tests = {
        {"should_return_x_plus_2_given_status_is_fast_command_is_M_and_facing_is_E",
         ShouldReturnXPlus2GivenFastAndMAndFacingEast},
        {"should_return_N_and_x_plus_1_given_status_is_fast_command_is_L_and_facing_is_E",
         ShouldReturnNorthAndXPlus1GivenFastAndLAndFacingEast},
        {"should_return_S_and_x_plus_1_given_status_is_fast_given_command_is_R_and_facing_is_E",
         ShouldReturnSouthAndXPlus1GivenFastAndRAndFacingEast},
        {"should_return_y_plus_1_given_command_is_FFM_and_facing_is_N",
         ShouldReturnYPlus1GivenCommandIsFFMAndFacingNorth},
    };
    return Run(tests);
}
