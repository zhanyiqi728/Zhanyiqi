#include "ExecutorImpl.hpp"

#include <memory>

namespace adas {
namespace {

void MoveForward(Pose& pose) noexcept {
    switch (pose.heading) {
        case 'N': ++pose.y; break;
        case 'S': --pose.y; break;
        case 'E': ++pose.x; break;
        case 'W': --pose.x; break;
        default: break;
    }
}

char TurnLeftHeading(char heading) noexcept {
    switch (heading) {
        case 'N': return 'W';
        case 'W': return 'S';
        case 'S': return 'E';
        case 'E': return 'N';
        default: return heading;
    }
}

char TurnRightHeading(char heading) noexcept {
    switch (heading) {
        case 'N': return 'E';
        case 'E': return 'S';
        case 'S': return 'W';
        case 'W': return 'N';
        default: return heading;
    }
}

}  // namespace

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose_(pose) {}

void ExecutorImpl::Execute(const std::string& commands) noexcept {
    for (const char cmd : commands) {
        std::unique_ptr<ICommand> cmder;
        if (cmd == 'M') {
            cmder = std::make_unique<MoveCommand>();
        } else if (cmd == 'L') {
            cmder = std::make_unique<TurnLeftCommand>();
        } else if (cmd == 'R') {
            cmder = std::make_unique<TurnRightCommand>();
        } else if (cmd == 'F') {
            cmder = std::make_unique<FastCommand>();
        }
        if (cmder) {
            cmder->DoOperate(*this);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept {
    return pose_;
}

void ExecutorImpl::Move() noexcept {
    MoveForward(pose_);
}

void ExecutorImpl::TurnLeft() noexcept {
    pose_.heading = TurnLeftHeading(pose_.heading);
}

void ExecutorImpl::TurnRight() noexcept {
    pose_.heading = TurnRightHeading(pose_.heading);
}

void ExecutorImpl::Fast() noexcept {
    fast_ = !fast_;
}

bool ExecutorImpl::IsFast() const noexcept {
    return fast_;
}

}  // namespace adas
