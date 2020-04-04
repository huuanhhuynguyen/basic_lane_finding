cmake_minimum_required(VERSION 3.15)

set(THIS self_01_lane_finding_basic_cpp)
project(${THIS})

find_package( OpenCV REQUIRED )
find_package(Boost COMPONENTS system filesystem REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(SOURCES src/main.cpp include/read.h)

include_directories(include)
add_executable(${THIS} ${SOURCES})

target_link_libraries( ${THIS} ${OpenCV_LIBS})
target_link_libraries( ${THIS} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})