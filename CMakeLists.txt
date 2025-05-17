cmake_minimum_required(VERSION 3.10)
project(CompareIt)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

#include(FetchContent)
#
#FetchContent_Declare(
#  fltk
#  GIT_REPOSITORY https://github.com/fltk/fltk.git
#  GIT_TAG master  # You can specify a stable release tag instead
#)
#
#FetchContent_MakeAvailable(fltk)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(CompareIt ${SRC_FILES})

target_include_directories(CompareIt PRIVATE src src/Entries src/Comparison)
#target_link_libraries(CompareIt fltk)
#set_target_properties(CompareIt PROPERTIES WIN32_EXECUTABLE YES)
