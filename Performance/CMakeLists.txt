cmake_minimum_required(VERSION 3.28)
project(Cpp_Playground)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)


add_library(compilation_flags INTERFACE)
target_compile_options(compilation_flags
INTERFACE
    -g
    -O3
    -mavx2
    -Wall
    -pedantic
    -gdwarf-4
)

add_subdirectory(src)
