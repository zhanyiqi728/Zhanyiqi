# 实验二：面向对象编程

## 需求

在实验一 ADAS `Executor` 执行器基础上，使用面向对象编程的封装、继承与多态重构代码，并新增加速指令 `F`：

- 基础指令（与实验一一致）：
  - `M` 沿当前朝向前进 1 格
  - `L` 左转 90 度
  - `R` 右转 90 度
- 新增加速指令 `F`：接收到后进入加速状态，再次收到 `F` 时取消（状态翻转）。
- 加速状态下：
  - `M` 前进 2 格（不能跳跃，一格一格前进）
  - `L` 先前进 1 格，然后左转 90 度
  - `R` 先前进 1 格，然后右转 90 度

未传初始位置时默认为 `(0, 0, N)`。课件假设调用参数合法且坐标运算不会超出 `int32` 范围。

## 面向对象设计

按照课件的重构步骤，将面向过程的 `if/else` 实现逐步改造为面向对象结构：

1. **封装**：把指令处理逻辑抽取为 `Move()`、`TurnLeft()`、`TurnRight()` 成员函数，降低圈复杂度。
2. **接口抽象与多态**：定义虚基类 `ICommand`，抽象方法 `DoOperate(ExecutorImpl&)`；
   `MoveCommand`、`TurnLeftCommand`、`TurnRightCommand` 继承 `ICommand`，各自实现具体操作。
3. **扩展**：新增 `FastCommand` 继承 `ICommand`，`Execute()` 中统一通过 `ICommand` 指针分发，新增指令时只需新增一个类，无需改动分发逻辑。

## 目录

- `include/Executor.hpp`：对外接口与位置类型 `Pose`
- `src/ExecutorImpl.hpp`、`src/ExecutorImpl.cpp`：执行器实现，含 `ICommand` 及各类指令
- `tests/TestSupport.hpp`：轻量测试框架（`ExpectPose` / `Run`）
- `tests/ExecutorTest.cpp`：基础指令测试，覆盖默认/初始状态、四个方向移动、转向、组合指令和空指令
- `tests/ExecutorFastTest.cpp`：`F` 指令测试，覆盖加速状态下的 `M`/`L`/`R` 及再次 `F` 取消状态

## 构建和运行

需要支持 C++17 的编译器及 CMake 3.16 或更新版本。

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## 版本管理建议

按课件的小步提交方式，每完成一步编译运行验证后及时入库：

```text
refactor: extract Move/TurnLeft/TurnRight member functions
refactor: wrap commands into MoveCommand/TurnLeftCommand/TurnRightCommand
refactor: abstract ICommand interface with inheritance and polymorphism
feat: implement FastCommand and fast-state behavior
test: cover fast command M/L/R and F toggle
```
