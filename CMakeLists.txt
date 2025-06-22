cmake_minimum_required(VERSION 3.10)
project(CompareIt)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_AUTOMOC ON) # Enables Meta-Object Compiler
set(CMAKE_AUTORCC ON) # Enables Qt Resource Compiler
set(CMAKE_AUTOUIC ON) # Enables UI file support

find_package(Qt6 REQUIRED COMPONENTS Widgets)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(CompareIt ${SRC_FILES})

target_include_directories(
    CompareIt
    PRIVATE src src/Entries src/Comparison src/Core src/UI
)

target_link_libraries(CompareIt Qt6::Widgets)
