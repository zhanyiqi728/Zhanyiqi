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

// 正常掉头：左转 -> 前进 1 -> 左转，最终面向西。
void ShouldNormalTRBuildLeftForwardLeft() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("TR");
    ExpectPose(executor->Query(), {0, 1, 'W'}, __func__);
}

// 加速掉头：前进 -> 左转 -> 前进 -> 左转。
void ShouldFastTRBuildForwardLeftForwardLeft() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("FTR");
    ExpectPose(executor->Query(), {1, 1, 'W'}, __func__);
}

// 倒车状态下掉头指令被忽略。
void InTheBStateTheReverseCommandWillBeIgnored() {
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    if (!executor) std::exit(EXIT_FAILURE);
    executor->Execute("BTR");
    ExpectPose(executor->Query(), {0, 0, 'E'}, __func__);
}

}  // namespace

int main() {
    const std::vector<TestCase> tests = {
        {"should_normal_tr_build_left_forward_left",
         ShouldNormalTRBuildLeftForwardLeft},
        {"should_fast_tr_build_forward_left_forward_left",
         ShouldFastTRBuildForwardLeftForwardLeft},
        {"in_the_B_state_the_reverse_command_will_be_ignored",
         InTheBStateTheReverseCommandWillBeIgnored},
    };
    return Run(tests);
}
