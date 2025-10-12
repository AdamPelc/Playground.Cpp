add_library(CustomIterator.Vector)

target_link_libraries(CustomIterator.Vector PRIVATE fmt::fmt)
target_compile_options(CustomIterator.Vector PRIVATE -std=c++20)

target_sources(CustomIterator.Vector PRIVATE Vector.cpp)

target_include_directories(CustomIterator.Vector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(UT)
