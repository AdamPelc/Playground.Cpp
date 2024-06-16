cmake_minimum_required(VERSION 3.22)
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

########################################################################################################################
# Playgrounds
########################################################################################################################
add_subdirectory(Book)
add_subdirectory(CustomIterator)
add_subdirectory(InstructionLevelParallelism)
add_subdirectory(LeetCode)
add_subdirectory(P001.VisitorDesignPattern)
add_subdirectory(P002.VisitorDesignPatternGeneric)
add_subdirectory(P003.Spectre)
