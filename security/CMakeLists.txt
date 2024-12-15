cmake_minimum_required(VERSION 3.24...3.30)
project(poly-security LANGUAGES CXX)

add_executable(poly-security
    ${CMAKE_CURRENT_SOURCE_DIR}/src/security.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../tests/src/classes.cpp
)

target_include_directories(poly-security PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../poly/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../tests/src/
)

target_link_libraries(poly-security PRIVATE poly)
