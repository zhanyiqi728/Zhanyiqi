# 实验三（二）：面向函数式编程

## 需求

在实验三（一）的基础上，用函数式编程替代继承多态，实现同样的 ADAS 指令语义：

- 基础指令：`M` 前进 1 格、`L` 左转 90 度、`R` 右转 90 度。
- 加速指令 `F`：切换加速状态，加速态下 `M` 前进 2 格、`L`/`R` 先前进 1 格再转。
- 倒车指令 `B`：切换倒车状态，倒车态下 `M` 后退 1 格、`L`/`R` 变成反方向转向。
- `B` 与 `F` 正交叠加：叠加态下 `M` 后退 2 格、`L`/`R` 先后退 1 格再反方向转向。

## 函数式设计

1. **移除 `ICommand`**：指令不再是继承体系中的子类，而是各自独立的函数对象（`operator()` 重载）。
2. **`std::function` 表驱动**：`Execute` 用 `std::unordered_map<char, std::function<void(PoseHandler&)>>` 以初始值列表一次构建完成，指令对象被隐式转换为 `std::function`。
3. **生命周期安全**：表里存的是可拷贝的函数对象而非 `std::function` 成员引用，避免悬空引用问题。

状态抽象（`Point` / `Direction` 数值编码）与实验三（一）保持一致。

## 目录

- `include/Executor.hpp`：对外接口与 `Pose` 类型
- `src/Point.hpp/.cpp`、`src/Direction.hpp/.cpp`、`src/PoseHandler.hpp/.cpp`：状态数据封装
- `src/Command.hpp`：函数对象指令（`operator()` 重载）
- `src/ExecutorImpl.hpp/.cpp`：执行器实现（`std::function` 表驱动）
- `tests/`：`ExecutorTest`（基础）、`ExecutorFastTest`（F）、`ExecutorReverseTest`（B 正交分解）

## 构建和运行

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
