cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project (poly)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Ofast -Wno-dollar-in-identifier-extension")

set(
    SHARED_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/poly.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/poly_v3.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/poly_v4.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/poly_v5.hpp
)

set(
    DEV_SOURCE_FILES
    ${SHARED_SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/poly_dev.cpp
)

set(
    BENCHMARK_SOURCE_FILES
    ${SHARED_SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmark.cpp
)

add_executable(poly_dev ${DEV_SOURCE_FILES})
target_include_directories(
    poly_dev PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(benchmark ${BENCHMARK_SOURCE_FILES})
target_include_directories(
    benchmark PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)