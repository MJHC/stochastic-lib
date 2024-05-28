cmake_minimum_required(VERSION 3.15)
project(stochastic_lib VERSION 1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)


include(cmake/benchmark.cmake)
include(cmake/doctest.cmake)

enable_testing()

include_directories(include/stochastic_lib)
add_subdirectory(src/stochastic_lib)

add_subdirectory(test)
add_subdirectory(benchmark)