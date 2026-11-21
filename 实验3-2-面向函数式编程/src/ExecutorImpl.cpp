#include "ExecutorImpl.hpp"

#include <functional>
#include <unordered_map>

#include "Command.hpp"

namespace adas {

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose) {}

void ExecutorImpl::Execute(const std::string& commands) noexcept {
    // 函数式表驱动：以字符为键映射函数对象，初始值列表一次构建完成。
    const std::unordered_map<char, std::function<void(PoseHandler&)>> cmderMap {
        {'M', MoveCommand()},
        {'L', TurnLeftCommand()},
        {'R', TurnRightCommand()},
        {'F', FastCommand()},
        {'B', ReverseCommand()},
    };

    for (const char cmd : commands) {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end()) {
            it->second(poseHandler);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept {
    return poseHandler.Query();
}

}  // namespace adas
