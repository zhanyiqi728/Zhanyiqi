#pragma once

#include <string>

namespace adas {

struct Pose {
    int x;
    int y;
    char heading;
};

bool operator==(const Pose& lhs, const Pose& rhs) noexcept;

class Executor {
public:
    // The caller owns the returned object and must delete it.
    static Executor* NewExecutor(const Pose& pose = {0, 0, 'N'}) noexcept;

    Executor() = default;
    virtual ~Executor() = default;

    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;

    virtual void Execute(const std::string& commands) noexcept = 0;
    virtual Pose Query() const noexcept = 0;
};

}  // namespace adas
