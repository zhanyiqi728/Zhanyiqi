#pragma once

#include "ActionGroup.hpp"

namespace adas {

// 移动指令：确定单步动作为前进或后退，加速状态执行两遍。
class MoveCommand final {
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept {
        ActionGroup actionGroup;
        const auto action = poseHandler.IsReverse()
                                ? ActionType::BACKWARD_1_STEP_ACTION
                                : ActionType::FORWARD_1_STEP_ACTION;
        if (poseHandler.IsFast()) {
            actionGroup.PushAction(action);
        }
        actionGroup.PushAction(action);
        return actionGroup;
    }
};

// 左转指令：加速状态先移动，倒车状态下左转变成右转。
class TurnLeftCommand final {
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept {
        ActionGroup actionGroup;
        if (poseHandler.IsFast()) {
            actionGroup.PushAction(poseHandler.IsReverse()
                                       ? ActionType::BACKWARD_1_STEP_ACTION
                                       : ActionType::FORWARD_1_STEP_ACTION);
        }
        actionGroup.PushAction(poseHandler.IsReverse()
                                   ? ActionType::REVERSE_TURNLEFT_ACTION
                                   : ActionType::TURNLEFT_ACTION);
        return actionGroup;
    }
};

// 右转指令：加速状态先移动，倒车状态下右转变成左转。
class TurnRightCommand final {
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept {
        ActionGroup actionGroup;
        if (poseHandler.IsFast()) {
            actionGroup.PushAction(poseHandler.IsReverse()
                                       ? ActionType::BACKWARD_1_STEP_ACTION
                                       : ActionType::FORWARD_1_STEP_ACTION);
        }
        actionGroup.PushAction(poseHandler.IsReverse()
                                   ? ActionType::REVERSE_TURNRIGHT_ACTION
                                   : ActionType::TURNRIGHT_ACTION);
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
