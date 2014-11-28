# CMake configuration for ttmath
cmake_minimum_required (VERSION 3.0)
project(ttmath)
enable_testing()
include_directories(${ttmath_SOURCE_DIR})
add_subdirectory(samples)
