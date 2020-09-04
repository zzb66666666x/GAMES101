cmake_minimum_required(VERSION 3.10)
project(Rasterizer)

set(LIBS D:/CodingLibs)
set(OpenCV_DIR ${LIBS}/opencv/mingw_build)
find_package(OpenCV REQUIRED)

set(INCLUDE_DIR ${LIBS})
include_directories(${INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)

add_executable(Rasterizer main.cpp rasterizer.hpp rasterizer.cpp global.hpp Triangle.hpp Triangle.cpp)
target_link_libraries(Rasterizer ${OpenCV_LIBRARIES})
