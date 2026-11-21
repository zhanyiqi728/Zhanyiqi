# 实验三（一）：面向对象编程

## 需求

在实验二 ADAS `Executor` 基础上，新增倒车指令 `B`，并通过数据抽离、表驱动和状态抽象优化面向对象结构：

- 基础指令：`M` 前进 1 格、`L` 左转 90 度、`R` 右转 90 度。
- 加速指令 `F`：切换加速状态，加速态下 `M` 前进 2 格、`L`/`R` 先前进 1 格再转。
- 倒车指令 `B`：切换倒车状态，倒车态下 `M` 后退 1 格、`L`/`R` 变成反方向转向（位置不变）。
- `B` 与 `F` 可叠加：叠加态下 `M` 后退 2 格、`L`/`R` 先后退 1 格再反方向转向。

## 面向对象设计

1. **数据抽离解耦循环依赖**：把 `ExecutorImpl` 中的状态数据（位置、朝向、加速/倒车标志）抽离到 `PoseHandler`，使指令类只依赖 `PoseHandler` 而非 `ExecutorImpl`。
2. **表驱动消减圈复杂度**：`Execute` 中用 `std::unordered_map<char, std::unique_ptr<ICommand>>` 以字符为键映射指令对象，消除 `if/else` 分支。
3. **状态抽象**：`Point` 封装位置变化向量，`Direction` 用 `E/S/W/N` 的数值编码，左转 `(index+3)%4`、右转 `(index+1)%4`，将复杂状态流转简化为算术运算。

## 目录

- `include/Executor.hpp`：对外接口与 `Pose` 类型
- `src/Point.hpp/.cpp`：位置信息封装
- `src/Direction.hpp/.cpp`：朝向数值化抽象
- `src/PoseHandler.hpp/.cpp`：状态数据封装
- `src/Command.hpp`：`ICommand` 接口及各指令类
- `src/ExecutorImpl.hpp/.cpp`：执行器实现（表驱动）
- `tests/`：`ExecutorTest`（基础）、`ExecutorFastTest`（F）、`ExecutorReverseTest`（B）

## 构建和运行

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
