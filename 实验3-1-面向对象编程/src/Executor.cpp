#include "Executor.hpp"

#include <new>
#include <tuple>

#include "ExecutorImpl.hpp"

namespace adas {

bool operator==(const Pose& lhs, const Pose& rhs) noexcept {
    return std::tie(lhs.x, lhs.y, lhs.heading) ==
           std::tie(rhs.x, rhs.y, rhs.heading);
}

Executor* Executor::NewExecutor(const Pose& pose) noexcept {
    return new (std::nothrow) ExecutorImpl(pose);
}

}  // namespace adas
