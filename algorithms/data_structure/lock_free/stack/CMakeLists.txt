# Thread sanitizer
add_library(thread_sanitizer INTERFACE)
target_compile_options(thread_sanitizer
INTERFACE
    -fsanitize=thread
    -g
)
target_link_options(thread_sanitizer
INTERFACE
    -fsanitize=thread
)

# Child directories to be included
add_subdirectory(benchmark)
add_subdirectory(lib)
add_subdirectory(test)
