cmake_minimum_required(VERSION 3.24...3.30)
project(poly LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Sanitizer is enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wno-array-bounds -g -fsanitize=leak")
    add_subdirectory(security)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -O3 -Wno-array-bounds")
endif()

add_subdirectory(poly)
add_subdirectory(tests)
add_subdirectory(benchmarks)
add_subdirectory(samples)
