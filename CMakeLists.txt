cmake_minimum_required(VERSION 3.3)
project(all_tests)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -std=c++17 -fPIC -pthread")

add_definitions(-DTEST_ENABLE)

include_directories(src src/test)
file(GLOB_RECURSE ALL_LIBRIRY_SRCS "src/*.c*")

add_executable(${PROJECT_NAME} ${ALL_LIBRIRY_SRCS})
