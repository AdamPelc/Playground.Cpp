add_library(lf_stack STATIC)

target_include_directories(lf_stack
PUBLIC
    include
)

target_link_libraries(lf_stack
PRIVATE
    compiler_warnings
    compiler_features
    thread_sanitizer
)

add_subdirectory(src)
