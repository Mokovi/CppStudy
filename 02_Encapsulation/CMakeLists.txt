cmake_minimum_required(VERSION 3.15)
project(CAL)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
file(GLOB SrcList ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(CA ${SrcList})