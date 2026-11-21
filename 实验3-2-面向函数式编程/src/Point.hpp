#pragma once

namespace adas {

// 位置信息的封装，将四个方向上的位置变化统一到一个模型上。
class Point final {
public:
    Point(const int x, const int y) noexcept;
    Point(const Point& rhs) noexcept = default;
    Point& operator=(const Point& rhs) noexcept = default;

    Point& operator+=(const Point& rhs) noexcept;
    Point& operator-=(const Point& rhs) noexcept;

    int GetX(void) const noexcept;
    int GetY(void) const noexcept;

private:
    int x;
    int y;
};

}  // namespace adas
