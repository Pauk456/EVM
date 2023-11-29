cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

project(Lab7)

set(exe_name Lab7)

set(test_prim test_prim)
set(test_vectoriz test_vectoriz)
set(test_blas test_blas)

set(Matrix_prim Matrix_prim)
set(Matrix_vectoriz Matrix_vectoriz)
set(Matrix_blas Matrix_blas)

set(Boost_INCLUDE_DIR /usr/local/include/openblas)
set(Boost_LIBRARY_DIR /usr/local/lib)
find_package(OpenBLAS)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_library(${Matrix_prim}
    src/Mul_Matrix_prim.cpp
)

add_library(${Matrix_vectoriz}
    src/Mul_Matrix_vectoriz.cpp
)

add_library(${Matrix_blas}
    src/Matrix_BLAS.cpp
)

target_include_directories(Matrix_prim
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(Matrix_vectoriz
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(Matrix_blas
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(${exe_name} src/main.cpp)

target_link_libraries(${exe_name} ${Matrix_prim} ${Matrix_vectoriz} ${Matrix_blas} libopenblas) 

# ========== GoogleTest ==========

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${test_prim} test/test1.cpp )
target_link_libraries(${test_prim} gtest_main ${Matrix_prim})

add_executable(${test_vectoriz} test/test2.cpp)
target_link_libraries(${test_vectoriz} gtest_main ${Matrix_vectoriz})

add_executable(${test_blas} test/test3.cpp)
target_link_libraries(${test_blas} gtest_main ${Matrix_blas})
