add_library(lf_stack STATIC)

target_include_directories(lf_stack
PUBLIC
    include
)

target_link_libraries(lf_stack
PRIVATE
    compiler_warnings
    cpp_ver_23
    #thread_sanitizer
)

target_compile_options(lf_stack
PRIVATE
    -mcx16
)

add_subdirectory(src)
