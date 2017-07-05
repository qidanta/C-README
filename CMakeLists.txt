cmake_minimum_required(VERSION 3.3)
project(readme)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp str/segmentation.h)
add_executable(readme ${SOURCE_FILES})