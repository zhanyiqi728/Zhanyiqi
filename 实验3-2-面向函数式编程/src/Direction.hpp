#pragma once

#include "Point.hpp"

namespace adas {

// 朝向的数值化抽象：每个方向上的变化只有移动、左转、右转三种。
class Direction final {
public:
    static const Direction& GetDirection(const char heading) noexcept;

    Direction(const unsigned index, const char heading) noexcept;

    const Point& Move(void) const noexcept;
    const Direction& LeftOne(void) const noexcept;
    const Direction& RightOne(void) const noexcept;
    char GetHeading(void) const noexcept;

private:
    unsigned index;
    char heading;
};

}  // namespace adas
