#pragma once

#include "ActionGroup.hpp"

namespace adas {

// 移动指令：步长由车辆类型决定（普通车/大巴 1 格，跑车 2 格），
// 加速状态步长翻倍，倒车状态后退。
class MoveCommand final {
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept {
        ActionGroup actionGroup;
        const auto action = poseHandler.IsReverse()
                                ? ActionType::BACKWARD_1_STEP_ACTION
                                : ActionType::FORWARD_1_STEP_ACTION;
        const bool isSportsCar =
            poseHandler.GetVehicleType() == VehicleType::SportsCar;
        const unsigned baseSteps = isSportsCar ? 2u : 1u;
        const unsigned steps = poseHandler.IsFast() ? baseSteps * 2u : baseSteps;
        for (unsigned i = 0; i < steps; ++i) {
            actionGroup.PushAction(action);
        }
        return actionGroup;
    }
};

// 左转指令：不同车辆类型的移动/转向顺序不同，倒车状态下左转变成右转。
class TurnLeftCommand final {
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept {
        ActionGroup actionGroup;
        const auto step = poseHandler.IsReverse()
                              ? ActionType::BACKWARD_1_STEP_ACTION
                              : ActionType::FORWARD_1_STEP_ACTION;
        const auto turn = poseHandler.IsReverse()
                              ? ActionType::REVERSE_TURNLEFT_ACTION
                              : ActionType::TURNLEFT_ACTION;
        switch (poseHandler.GetVehicleType()) {
            case VehicleType::Bus:
                // 大巴：先移动（正常 1 格 / 加速 2 格），再转向。
                actionGroup.PushAction(step);
                if (poseHandler.IsFast()) {
                    actionGroup.PushAction(step);
                }
                actionGroup.PushAction(turn);
                break;
            case VehicleType::SportsCar:
                // 跑车：先转向再移动 1 格；加速时前后各移动 1 格。
                if (poseHandler.IsFast()) {
                    actionGroup.PushAction(step);
                }
                actionGroup.PushAction(turn);
                actionGroup.PushAction(step);
                break;
            case VehicleType::Normal:
            default:
                // 普通车：正常只转向；加速时先移动 1 格再转向。
                if (poseHandler.IsFast()) {
                    actionGroup.PushAction(step);
                }
                actionGroup.PushAction(turn);
                break;
        }
        return actionGroup;
    }
};

// 右转指令：与左转指令对称，倒车状态下右转变成左转。
class TurnRightCommand final {
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept {
        ActionGroup actionGroup;
        const auto step = poseHandler.IsReverse()
                              ? ActionType::BACKWARD_1_STEP_ACTION
                              : ActionType::FORWARD_1_STEP_ACTION;
        const auto turn = poseHandler.IsReverse()
                              ? ActionType::REVERSE_TURNRIGHT_ACTION
                              : ActionType::TURNRIGHT_ACTION;
        switch (poseHandler.GetVehicleType()) {
            case VehicleType::Bus:
                actionGroup.PushAction(step);
                if (poseHandler.IsFast()) {
                    actionGroup.PushAction(step);
                }
                actionGroup.PushAction(turn);
                break;
            case VehicleType::SportsCar:
                if (poseHandler.IsFast()) {
                    actionGroup.PushAction(step);
                }
                actionGroup.PushAction(turn);
                actionGroup.PushAction(step);
                break;
            case VehicleType::Normal:
            default:
                if (poseHandler.IsFast()) {
                    actionGroup.PushAction(step);
                }
                actionGroup.PushAction(turn);
                break;
        }
        return actionGroup;
    }
};

// 加速指令：切换加速状态。
class FastCommand final {
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept {
        return ActionGroup({ActionType::BE_FAST_ACTION});
    }
};

// 倒车指令：切换倒车状态。
class ReverseCommand final {
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept {
        return ActionGroup({ActionType::BE_REVERSE_ACTION});
    }
};

// 掉头指令：左转 90 -> 前进 1 -> 左转 90；倒车状态忽略，加速状态先前进 1 格再掉头。
class TurnRoundCommand final {
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept {
        if (poseHandler.IsReverse()) {
            return ActionGroup();
        }
        if (poseHandler.IsFast()) {
            return ActionGroup({ActionType::FORWARD_1_STEP_ACTION,
                                ActionType::TURNLEFT_ACTION,
                                ActionType::FORWARD_1_STEP_ACTION,
                                ActionType::TURNLEFT_ACTION});
        }
        return ActionGroup({ActionType::TURNLEFT_ACTION,
                            ActionType::FORWARD_1_STEP_ACTION,
                            ActionType::TURNLEFT_ACTION});
    }
};

}  // namespace adas
