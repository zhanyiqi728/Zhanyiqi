#pragma once

#include "Direction.hpp"
#include "Executor.hpp"

namespace adas {

// 抽离 ExecutorImpl 的状态数据，消除 Command 与 ExecutorImpl 之间的循环依赖。
class PoseHandler final {
public:
    explicit PoseHandler(const Pose& pose) noexcept;

    PoseHandler(const PoseHandler&) = delete;
    PoseHandler& operator=(const PoseHandler&) = delete;

    void Forward(void) noexcept;
    void Backward(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;

    void Fast(void) noexcept;
    bool IsFast(void) const noexcept;

    void Reverse(void) noexcept;
    bool IsReverse(void) const noexcept;

    Pose Query(void) const noexcept;

private:
    Point point;
    const Direction* facing;
    bool fast{false};
    bool reverse{false};
};

}  // namespace adas
