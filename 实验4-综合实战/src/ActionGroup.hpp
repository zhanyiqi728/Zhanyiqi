#pragma once

#include <cstdint>
#include <list>

#include "PoseHandler.hpp"

namespace adas {

// 原子动作类型：将指令拆解为不可再分的操作。
enum class ActionType : uint16_t {
    FORWARD_1_STEP_ACTION = 0,
    BACKWARD_1_STEP_ACTION,
    TURNLEFT_ACTION,
    REVERSE_TURNLEFT_ACTION,
    TURNRIGHT_ACTION,
    REVERSE_TURNRIGHT_ACTION,
    BE_FAST_ACTION,
    BE_REVERSE_ACTION,
};

// 动作组：一条指令编排出的一组原子动作。
class ActionGroup final {
public:
    ActionGroup() = default;
    explicit ActionGroup(const std::list<ActionType>& actions) noexcept;
    ~ActionGroup() = default;

    void PushAction(const ActionType actionType) noexcept;
    void DoOperate(PoseHandler& poseHandler) const noexcept;

private:
    std::list<ActionType> actions;
};

}  // namespace adas
