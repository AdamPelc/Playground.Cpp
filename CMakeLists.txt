cmake_minimum_required(VERSION 3.31)
project(Playground.Cpp)

########################################################################################################################
# Global Settings
########################################################################################################################
set(CMAKE_VERBOSE_MAKEFILE ON)

enable_testing()
########################################################################################################################
# 3PP Packages
########################################################################################################################
find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)

#########################################################################################################################
## Compiler options
#########################################################################################################################
# Version C++23
add_library(cpp_ver_23 INTERFACE)
target_compile_features(cpp_ver_23
    INTERFACE
    cxx_std_23
)
# Common compiler warnings
add_library(compiler_warnings INTERFACE)
target_compile_options(compiler_warnings
INTERFACE
    -Wall
    -Werror
    -Wextra
    -pedantic
)

########################################################################################################################
# Playgrounds
########################################################################################################################
add_subdirectory(algorithms)
add_subdirectory(Book)
add_subdirectory(CustomIterator)
add_subdirectory(LeetCode)
add_subdirectory(P001.VisitorDesignPattern)
add_subdirectory(P002.VisitorDesignPatternGeneric)
add_subdirectory(P003.Spectre)
add_subdirectory(performance)
add_subdirectory(queue)
