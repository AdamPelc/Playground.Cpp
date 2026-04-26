add_library(simd_01 STATIC)
target_sources(simd_01
PRIVATE
    simd.cpp
)
target_link_libraries(simd_01
PRIVATE
    compilation_flags
    compiler_warnings
    cpp_ver_23
)
target_include_directories(simd_01
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_options(simd_01
PRIVATE
    -fopt-info-vec-optimized
    -fopt-info-vec-missed
)

add_custom_target(simd_01.asm
    COMMAND ${CMAKE_CXX_COMPILER}
        -S -masm=intel -fverbose-asm
        -O3 -std=c++23 -mavx2 -DNDEBUG
        -I ${CMAKE_CURRENT_SOURCE_DIR}
        -o ${CMAKE_CURRENT_BINARY_DIR}/simd.s
        ${CMAKE_CURRENT_SOURCE_DIR}/simd.cpp
    COMMENT "Generating Intel assembly for simd_01"
)
