#pragma once

namespace adas {

// 线程安全单例模板：C++11 起函数内静态局部变量初始化保证线程安全。
template <typename T>
class Singleton final {
public:
    static T& Instance(void) noexcept {
        static T instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() = default;
    ~Singleton() = default;
};

}  // namespace adas
