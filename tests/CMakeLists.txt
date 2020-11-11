set(THIS gtest_run)
project(unit_tests)

add_definitions( -DPROJECT_ROOT="${CMAKE_SOURCE_DIR}")

# include googletest from https://github.com/google/googletest
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# compile unit tests and link with googletest above
file(GLOB TEST_SOURCES "*.cpp")
add_executable(${THIS} ${TEST_SOURCES})
target_link_libraries(${THIS} gtest gtest_main)

# OpenCV needs to be installed
find_package(OpenCV REQUIRED)
target_link_libraries(${THIS} ${OpenCV_LIBS})

# Boost needs to be installed
find_package(Boost COMPONENTS system filesystem REQUIRED)
target_link_libraries(${THIS} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
