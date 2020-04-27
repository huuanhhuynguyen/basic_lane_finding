cmake_minimum_required(VERSION 3.10)

set(THIS basic_lane_finding_cpp)
project(${THIS})

set(CMAKE_CXX_STANDARD 14)
file(GLOB HEADERS "include/*.h")
file(GLOB SOURCES "src/*.cpp")

include_directories(include)
add_executable(${THIS} ${HEADERS} ${SOURCES})

# OpenCV needs to be installed
find_package(OpenCV REQUIRED)
target_link_libraries(${THIS} ${OpenCV_LIBS})

# Boost needs to be installed
find_package(Boost COMPONENTS system filesystem REQUIRED)
target_link_libraries(${THIS} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})