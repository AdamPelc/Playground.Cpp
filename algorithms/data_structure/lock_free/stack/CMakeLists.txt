# Common compiler warnings
add_library(compiler_warnings INTERFACE)
target_compile_options(compiler_warnings
INTERFACE
    -Wall
    -Werror
    -Wextra
    -pedantic
)

# Common compiler features
add_library(compiler_features INTERFACE)
target_compile_features(compiler_features
INTERFACE
    cxx_std_20
)

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
