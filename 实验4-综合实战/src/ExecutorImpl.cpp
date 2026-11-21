#include "ExecutorImpl.hpp"

#include <algorithm>

#include "CmderFactory.hpp"
#include "Singleton.hpp"

namespace adas {

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose) {}

void ExecutorImpl::Execute(const std::string& commands) noexcept {
    const auto cmders =
        Singleton<CmderFactory>::Instance().GetCmders(commands);
    std::for_each(cmders.begin(), cmders.end(),
                  [this](const Cmder& cmder) noexcept {
                      cmder(poseHandler).DoOperate(poseHandler);
                  });
}

Pose ExecutorImpl::Query() const noexcept {
    return poseHandler.Query();
}

}  // namespace adas
