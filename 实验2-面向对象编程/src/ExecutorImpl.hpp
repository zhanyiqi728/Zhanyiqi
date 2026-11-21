#pragma once

#include "Executor.hpp"

namespace adas {

class ExecutorImpl final : public Executor {
public:
    explicit ExecutorImpl(const Pose& pose) noexcept;

    void Execute(const std::string& commands) noexcept override;
    Pose Query() const noexcept override;

private:
    // 基础行为：移动 / 左转 / 右转，以及加速状态切换。
    void Move() noexcept;
    void TurnLeft() noexcept;
    void TurnRight() noexcept;
    void Fast() noexcept;
    bool IsFast() const noexcept;

    // 指令处理接口：面向对象的封装，统一抽象行为。
    class ICommand {
    public:
        virtual ~ICommand() = default;
        virtual void DoOperate(ExecutorImpl& executor) const noexcept = 0;
    };

    // 移动指令：加速状态下前进 2 格（一格一格前进），否则前进 1 格。
    class MoveCommand final : public ICommand {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override {
            if (executor.IsFast()) {
                executor.Move();
            }
            executor.Move();
        }
    };

    // 左转指令：加速状态下先前进 1 格再左转，否则仅左转。
    class TurnLeftCommand final : public ICommand {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override {
            if (executor.IsFast()) {
                executor.Move();
            }
            executor.TurnLeft();
        }
    };

    // 右转指令：加速状态下先前进 1 格再右转，否则仅右转。
    class TurnRightCommand final : public ICommand {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override {
            if (executor.IsFast()) {
                executor.Move();
            }
            executor.TurnRight();
        }
    };

    // 加速指令：切换加速状态（再次收到 F 时取消）。
    class FastCommand final : public ICommand {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override {
            executor.Fast();
        }
    };

    Pose pose_;
    bool fast_{false};
};

}  // namespace adas
