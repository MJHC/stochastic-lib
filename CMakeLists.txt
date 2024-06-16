cmake_minimum_required(VERSION 3.21)
project(stochastic_lib VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# set(BUILD_SHARED_LIBS OFF)
include(cmake/benchmark.cmake)
include(cmake/doctest.cmake)

enable_testing()

find_package(Python3 3.10 COMPONENTS Interpreter Development NumPy REQUIRED)
message(STATUS "Python executable: '${Python3_EXECUTABLE}'")
message(STATUS "Python include directories: '${Python3_INCLUDE_DIRS}'")
message(STATUS "Python libraries: '${Python3_LIBRARIES}'")

include_directories(${Python3_INCLUDE_DIRS})
include_directories(libs/matplotlib/include)

include_directories(include/stochastic_lib)

add_custom_target(build_src)
add_custom_target(build_test)
add_custom_target(build_benchmark)
add_custom_target(build_examples)

add_subdirectory(src/stochastic_lib)

add_subdirectory(test)
add_subdirectory(benchmark)
add_subdirectory(examples)
