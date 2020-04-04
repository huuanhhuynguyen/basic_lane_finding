cmake_minimum_required(VERSION 3.15)

set(THIS self_01_lane_finding_basic_cpp)

project(${THIS})

set(CMAKE_CXX_STANDARD 14)

set(SOURCES src/main.cpp)

add_executable(${THIS} ${SOURCES})