add_library(network_flow STATIC)
target_include_directories(network_flow
PUBLIC
    include
PRIVATE
    src
)
add_subdirectory(src)