cmake_minimum_required (VERSION 2.8.11)
project (Transformation)


set(EIGEN3_INCLUDE_DIR $ENV{LIBS}/eigen3)

include_directories(${EIGEN3_INCLUDE_DIR})

add_executable (Transformation main.cpp)
