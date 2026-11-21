#include "PoseHandler.hpp"

namespace adas {

PoseHandler::PoseHandler(const Pose& pose, const VehicleType type) noexcept
    : point(pose.x, pose.y),
      facing(&Direction::GetDirection(pose.heading)),
      vehicleType(type) {}

void PoseHandler::Forward(void) noexcept {
    point += facing->Move();
}

void PoseHandler::Backward(void) noexcept {
    point -= facing->Move();
}

void PoseHandler::TurnLeft(void) noexcept {
    facing = &facing->LeftOne();
}

void PoseHandler::TurnRight(void) noexcept {
    facing = &facing->RightOne();
}

void PoseHandler::Fast(void) noexcept {
    fast = !fast;
}

bool PoseHandler::IsFast(void) const noexcept {
    return fast;
}

void PoseHandler::Reverse(void) noexcept {
    reverse = !reverse;
}

bool PoseHandler::IsReverse(void) const noexcept {
    return reverse;
}

Pose PoseHandler::Query(void) const noexcept {
    return {point.GetX(), point.GetY(), facing->GetHeading()};
}

VehicleType PoseHandler::GetVehicleType(void) const noexcept {
    return vehicleType;
}

}  // namespace adas
