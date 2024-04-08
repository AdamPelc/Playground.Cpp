add_executable(01_substring_sort)

target_sources(01_substring_sort
    PRIVATE
    main.cpp
)

target_link_libraries(01_substring_sort PRIVATE compilation_flags compare)

add_library(compare SHARED)
target_sources(compare PRIVATE compare.cpp)
target_link_libraries(compare PRIVATE compilation_flags)
