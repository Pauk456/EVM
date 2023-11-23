cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

project(Lab7)

set(exe_name Lab7)

add_library(Matrix
    src/Mul_Matrix_prim.cpp
)

target_include_directories(Matrix
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(${exe_name} src/main.cpp)

target_link_libraries(${PROJECT_NAME} Matrix)
