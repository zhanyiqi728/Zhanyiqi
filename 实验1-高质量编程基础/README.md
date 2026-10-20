# 实验一：高质量编程基础

## 需求

实现 ADAS `Executor` 执行器：保存整数坐标和 `N/S/E/W` 朝向；`M` 沿当前朝向前进一格，`L` 左转 90 度，`R` 右转 90 度；`Query()` 返回当前位置。未传初始位置时默认为 `(0, 0, N)`。课件假设调用参数合法且坐标运算不会超出 `int32` 范围。

## 目录

- `include/Executor.hpp`：对外接口与位置类型
- `src/ExecutorImpl.hpp`、`src/ExecutorImpl.cpp`：执行器实现
- `tests/ExecutorTest.cpp`：独立测试程序，覆盖默认/初始状态、四个方向移动、转向、组合指令和空指令

## 构建和运行

需要支持 C++17 的编译器及 CMake 3.16 或更新版本。

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## 版本管理建议

按课件的小步提交方式，先提交测试用例，再提交对应实现；提交信息说明行为和变更目的，例如：

```text
test: cover default and initial executor poses
feat: implement executor movement and turns
```
