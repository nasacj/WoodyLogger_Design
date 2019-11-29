cmake_minimum_required(VERSION 3.10)
project(WoodyLogger)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3")

include_directories(.)
link_directories(.)

add_executable(demo demo.cpp)
target_link_libraries(demo pthread WoodyLogger)

add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark WoodyLogger pthread)
