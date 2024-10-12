cmake_minimum_required(VERSION 3.24...3.30)
project(poly-tests VERSION 1.0.0 LANGUAGES CXX)

include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(googletest)

add_executable(poly-tests
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tests.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/classes.cpp
)

target_include_directories(poly-tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../poly/include
)

target_link_libraries(poly-tests PRIVATE
    GTest::gtest_main
)

enable_testing()
gtest_discover_tests(poly-tests)
