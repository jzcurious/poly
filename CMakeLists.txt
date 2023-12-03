cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project (poly)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

set(
    SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/poly.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/poly_dev.cpp
)

add_executable(poly_dev ${SOURCE_FILES})

target_include_directories(
    poly_dev PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)