cmake_minimum_required(VERSION 3.24...3.30)
project(poly-samples LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(poly-sample
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sample.cpp
)

target_link_libraries(poly-sample PRIVATE
    poly
)
