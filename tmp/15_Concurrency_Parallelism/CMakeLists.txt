cmake_minimum_required(VERSION 3.15)
set(CXX_STANDARD_REQUIRED 17)
project(Concurrency)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB SrList ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
find_package(Threads REQUIRED)
add_executable(app ${SrList})
target_link_libraries(app PRIVATE Threads::Threads) #动态库链接在可执行文件生成后
