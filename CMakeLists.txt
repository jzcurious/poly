cmake_minimum_required(VERSION 3.24...3.30)
project(poly VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -O3 -Wno-array-bounds")

add_subdirectory(tests)
add_subdirectory(benchmarks)
