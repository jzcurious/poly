cmake_minimum_required(VERSION 3.24...3.30)
project(poly-benchmarks LANGUAGES CXX)

include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.9.0
)

FetchContent_MakeAvailable(benchmark)

add_executable(poly-benchmarks
    ${CMAKE_CURRENT_SOURCE_DIR}/src/benchmarks.cpp
)

target_include_directories(poly-benchmarks PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../poly/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(poly-benchmarks PRIVATE
    benchmark::benchmark
)
