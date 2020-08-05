cmake_minimum_required(VERSION 3.10)
project(testcv)

set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR D:/CodingLibs/opencv/mingw_build)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(testcv main.cpp)
target_link_libraries(testcv ${OpenCV_LIBRARIES})
