#[[
这是块注释
]]

# 这是单行注释
#[[
cmake_minimum_required(VERSION 3.15)
project(HelloWorld)
add_executable(HW 01_HelloWorld.cpp)
]]

cmake_minimum_required(VERSION 3.15)
project(HelloWorld)
set(SR_List 01_HelloWorld.cpp)
set(CMAKE_CXX_STANDARD 17) #CMAKE_CXX_STANDARD 宏 需要的c++版本
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin) #EXECUTABLE_OUTPUT_PATH 宏 可执行文件输出路径  CMAKE_CURRENT_SOURCE_DIR cmakelists.txt文件所在位置
add_executable(HW ${SR_List})