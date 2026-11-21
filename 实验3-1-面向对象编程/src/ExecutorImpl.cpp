#include "ExecutorImpl.hpp"

#include <memory>
#include <unordered_map>

#include "Command.hpp"

namespace adas {

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose) {}

void ExecutorImpl::Execute(const std::string& commands) noexcept {
    // 表驱动：以字符为键映射指令对象，避免冗长的 if/else 分支。
    std::unordered_map<char, std::unique_ptr<ICommand>> cmderMap;
    cmderMap.emplace('M', std::make_unique<MoveCommand>());
    cmderMap.emplace('L', std::make_unique<TurnLeftCommand>());
    cmderMap.emplace('R', std::make_unique<TurnRightCommand>());
    cmderMap.emplace('F', std::make_unique<FastCommand>());
    cmderMap.emplace('B', std::make_unique<ReverseCommand>());

    for (const char cmd : commands) {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end()) {
            it->second->DoOperate(poseHandler);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept {
    return poseHandler.Query();
}

}  // namespace adas
