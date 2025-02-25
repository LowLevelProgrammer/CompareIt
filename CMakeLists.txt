cmake_minimum_required(VERSION 3.30)
project(CompareIt)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(CompareIt ${SRC_FILES})

target_include_directories(CompareIt PRIVATE src)

