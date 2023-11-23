cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

project(Lab7)

set(exe_name Lab7)

set(test_name test)

add_library(Matrix
    src/Mul_Matrix_prim.cpp
)

target_include_directories(Matrix
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(${exe_name} src/main.cpp)

target_link_libraries(${PROJECT_NAME} Matrix)

# ========== GoogleTest ==========

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${test_name} test/test.cpp)
target_link_libraries(${test_name} gtest_main)
target_link_libraries(${test_name} Matrix)
