#pragma once

#include <string>

namespace adas {

// 车辆类型：决定 M/L/R 指令的编排方式。
enum class VehicleType {
    Normal,    // 普通车
    Bus,       // 大巴
    SportsCar, // 跑车
};

struct Pose {
    int x;
    int y;
    char heading;
};

bool operator==(const Pose& lhs, const Pose& rhs) noexcept;

class Executor {
public:
    // The caller owns the returned object and must delete it.
    static Executor* NewExecutor(
        const Pose& pose = {0, 0, 'N'},
        const VehicleType type = VehicleType::Normal) noexcept;

    Executor() = default;
    virtual ~Executor() = default;

    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;

    virtual void Execute(const std::string& commands) noexcept = 0;
    virtual Pose Query() const noexcept = 0;
};

}  // namespace adas
