#pragma once

#include "PoseHandler.hpp"

namespace adas {

// 指令处理接口：封装 + 继承 + 多态。
class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void DoOperate(PoseHandler& poseHandler) const noexcept = 0;
};

// 移动指令：加速/倒车状态决定前进或后退，加速状态加倍步数。
class MoveCommand final : public ICommand {
public:
    void DoOperate(PoseHandler& poseHandler) const noexcept override {
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
class TurnLeftCommand final : public ICommand {
public:
    void DoOperate(PoseHandler& poseHandler) const noexcept override {
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
class TurnRightCommand final : public ICommand {
public:
    void DoOperate(PoseHandler& poseHandler) const noexcept override {
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
class FastCommand final : public ICommand {
public:
    void DoOperate(PoseHandler& poseHandler) const noexcept override {
        poseHandler.Fast();
    }
};

// 倒车指令：切换倒车状态。
class ReverseCommand final : public ICommand {
public:
    void DoOperate(PoseHandler& poseHandler) const noexcept override {
        poseHandler.Reverse();
    }
};

}  // namespace adas
