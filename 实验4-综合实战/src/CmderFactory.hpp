#pragma once

#include <functional>
#include <list>
#include <string>
#include <string_view>
#include <unordered_map>

#include "Command.hpp"

namespace adas {

// 指令：接收状态处理器，返回编排好的动作组。
using Cmder = std::function<ActionGroup(PoseHandler& poseHandler)>;
using CmderList = std::list<Cmder>;

// 指令工厂：将指令串解析为指令列表，指令表在工厂内只构建一次。
class CmderFactory final {
public:
    CmderFactory(void) = default;
    ~CmderFactory(void) = default;

    CmderFactory(const CmderFactory&) noexcept = delete;
    CmderFactory& operator=(const CmderFactory&) noexcept = delete;

    CmderList GetCmders(const std::string& commands) const noexcept;

private:
    std::string ParseCommandString(std::string_view commands) const noexcept;
    void ReplaceAll(std::string& inout, std::string_view what,
                    std::string_view with) const noexcept;

private:
    const std::unordered_map<char, Cmder> cmderMap {
        {'M', MoveCommand()},
        {'L', TurnLeftCommand()},
        {'R', TurnRightCommand()},
        {'Z', TurnRoundCommand()},
        {'B', ReverseCommand()},
        {'F', FastCommand()},
    };
};

}  // namespace adas
