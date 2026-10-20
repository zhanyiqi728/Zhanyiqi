#pragma once

#include "Executor.hpp"

namespace adas {

class ExecutorImpl final : public Executor {
public:
    explicit ExecutorImpl(const Pose& pose) noexcept;

    void Execute(const std::string& commands) noexcept override;
    Pose Query() const noexcept override;

private:
    Pose pose_;
};

}  // namespace adas
