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

add_subdirectory(01_substring_sort)
