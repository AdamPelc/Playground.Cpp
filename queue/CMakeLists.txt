option(ENABLE_TSAN "Enable Thread Sanitizer" OFF)
if(ENABLE_TSAN)
    add_library(tsan INTERFACE)
    target_compile_options(tsan
    INTERFACE
        -g
        -fsanitize=thread
    )
    target_link_options(tsan
    INTERFACE
        -fsanitize=thread
    )
endif ()

add_subdirectory(lib)
add_subdirectory(benchmark)
add_subdirectory(test)
