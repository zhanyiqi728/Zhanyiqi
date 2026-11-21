#pragma once

#include "PoseHandler.hpp"

namespace adas {

// 函数对象：用 operator() 重载替代继承多态，避免 std::function 包裹成员时的生命周期问题。

// 移动指令：加速/倒车状态决定前进或后退，加速状态加倍步数。
class MoveCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept {
        if (poseHandler.IsFast()) {
            if (poseHandler.IsReverse()) {
                poseHandler.Backward();
            } else {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse()) {
            poseHandler.Backward();
        } else {
            poseHandler.Forward();
        }
    }
};

// 左转指令：加速状态先移动，倒车状态下左转变成右转。
class TurnLeftCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept {
        if (poseHandler.IsFast()) {
            if (poseHandler.IsReverse()) {
                poseHandler.Backward();
            } else {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse()) {
            poseHandler.TurnRight();
        } else {
            poseHandler.TurnLeft();
        }
    }
};

// 右转指令：加速状态先移动，倒车状态下右转变成左转。
class TurnRightCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept {
        if (poseHandler.IsFast()) {
            if (poseHandler.IsReverse()) {
                poseHandler.Backward();
            } else {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse()) {
            poseHandler.TurnLeft();
        } else {
            poseHandler.TurnRight();
        }
    }
};

// 加速指令：切换加速状态。
class FastCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept {
        poseHandler.Fast();
    }
};

// 倒车指令：切换倒车状态。
class ReverseCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept {
        poseHandler.Reverse();
    }
};

}  // namespace adas
