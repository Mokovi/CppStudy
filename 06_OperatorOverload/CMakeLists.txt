cmake_minimum_required(VERSION 3.15)
set(CXX_STANDARD_REQUIRED 17)
project(OperatorOverload)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB SR_LIST ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(app ${SR_LIST})