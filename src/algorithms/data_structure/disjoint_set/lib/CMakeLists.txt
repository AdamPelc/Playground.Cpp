add_library(disjoint_set STATIC)
target_include_directories(disjoint_set
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_sources(disjoint_set
PRIVATE
    disjoint_set.cpp
)
