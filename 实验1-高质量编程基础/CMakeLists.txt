cmake_minimum_required(VERSION 3.16)
project(adas_executor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(adas_executor
    src/Executor.cpp
    src/ExecutorImpl.cpp
)
target_include_directories(adas_executor PUBLIC include PRIVATE src)

add_executable(executor_tests tests/ExecutorTest.cpp)
target_link_libraries(executor_tests PRIVATE adas_executor)

enable_testing()
add_test(NAME executor_tests COMMAND executor_tests)
