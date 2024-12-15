cmake_minimum_required(VERSION 3.24)
project(poly-lib LANGUAGES CXX)

add_library(poly INTERFACE)

target_include_directories(poly INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/poly
)
