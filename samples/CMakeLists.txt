cmake_minimum_required(VERSION 3.24...3.30)
project(poly-samples VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -O3 -Wno-array-bounds")

add_executable(poly-sample
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sample.cpp
)

target_include_directories(poly-sample PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../poly/include
)
