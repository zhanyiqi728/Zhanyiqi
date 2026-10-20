#include "ExecutorImpl.hpp"

namespace adas {
namespace {

char TurnLeft(char heading) noexcept {
    switch (heading) {
        case 'N': return 'W';
        case 'W': return 'S';
        case 'S': return 'E';
        case 'E': return 'N';
        default: return heading;
    }
}

char TurnRight(char heading) noexcept {
    switch (heading) {
        case 'N': return 'E';
        case 'E': return 'S';
        case 'S': return 'W';
        case 'W': return 'N';
        default: return heading;
    }
}

void MoveForward(Pose& pose) noexcept {
    switch (pose.heading) {
        case 'N': ++pose.y; break;
        case 'S': --pose.y; break;
        case 'E': ++pose.x; break;
        case 'W': --pose.x; break;
        default: break;
    }
}

}  // namespace

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose_(pose) {}

void ExecutorImpl::Execute(const std::string& commands) noexcept {
    for (const char command : commands) {
        switch (command) {
            case 'M': MoveForward(pose_); break;
            case 'L': pose_.heading = TurnLeft(pose_.heading); break;
            case 'R': pose_.heading = TurnRight(pose_.heading); break;
            default: break;
        }
    }
}

Pose ExecutorImpl::Query() const noexcept {
    return pose_;
}

}  // namespace adas
