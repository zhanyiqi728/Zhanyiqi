# 实验四：综合实战

## 需求

在实验三（二）的基础上，通过面向接口编程与任务编排进一步重构，并新增掉头指令 `TR`：

- 基础指令：`M` 前进、`L` 左转、`R` 右转。
- 加速指令 `F`、倒车指令 `B`：切换对应状态，语义与实验三一致。
- 掉头指令 `TR`：
  - 正常：左转 90 -> 前进 1 -> 左转 90（面向反方向）。
  - 加速：前进 1 -> 左转 90 -> 前进 1 -> 左转 90。
  - 倒车：忽略（状态不变）。
- 支持不同车辆类型（作业）：`Normal` 普通车、`Bus` 大巴、`SportsCar` 跑车，`M`/`L`/`R` 语义随类型变化。

## 综合实战设计

1. **面向接口编程**：`Singleton<T>` 线程安全单例模板 + `CmderFactory` 指令工厂。指令表在工厂内只构建一次，`using Cmder = std::function<ActionGroup(PoseHandler&)>` 用别名简化签名。
2. **任务编排**：`ActionType` 枚举定义 8 种原子动作，`ActionGroup` 负责动作的收集与执行。指令不再直接操作状态，而是返回编排好的动作组，由 `Execute` 统一执行。
3. **掉头指令解析**：`CmderFactory` 先把 `TR` 替换为占位符 `Z`，再把 `Z` 映射到 `TurnRoundCommand`，避免与 `R`（右转）冲突。
4. **目录结构设计**：`include/`（对外接口）、`src/`（实现）、`tests/`（测试）分层。

## 目录

- `include/Executor.hpp`：对外接口与 `Pose` 类型
- `src/Singleton.hpp`：单例模板
- `src/ActionGroup.hpp/.cpp`：原子动作类型与动作组编排
- `src/Command.hpp`：指令函数对象（返回 `ActionGroup`）
- `src/CmderFactory.hpp/.cpp`：指令工厂与 `TR` 解析
- `src/Point`、`src/Direction`、`src/PoseHandler`：状态数据封装
- `src/ExecutorImpl.hpp/.cpp`：执行器实现
- `tests/`：`ExecutorTest`、`ExecutorFastTest`、`ExecutorReverseTest`、`ExecutorTurnRoundTest`、`ExecutorBusTest`、`ExecutorSportsCarTest`

## 构建和运行

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## 车辆类型（作业）

`Executor::NewExecutor(pose, type)` 通过 `VehicleType` 选择车辆类型，`PoseHandler` 保存类型，指令函数对象据此编排动作组：

- **Normal（普通车）**：`M` 前进 1 格（加速 2 格）；`L`/`R` 仅转向（加速时先移动 1 格）。
- **Bus（大巴）**：`M` 前进 1 格（加速 2 格）；`L`/`R` 先移动 1 格（加速 2 格）再转向。
- **SportsCar（跑车）**：`M` 前进 2 格（加速 4 格）；`L`/`R` 先转向再移动 1 格（加速时前后各移动 1 格）。

倒车状态下：`M` 后退、`L`/`R` 反向转向，与各类型的正常语义对应。
