add_library(simd_01.lib.02_vector_no_fast_math STATIC)
target_sources(simd_01.lib.02_vector_no_fast_math
    PRIVATE
        02_vector_no_fast_math.cpp
)
target_include_directories(simd_01.lib.02_vector_no_fast_math
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(simd_01.lib.02_vector_no_fast_math
    PUBLIC
        simd_01.lib.common
    PRIVATE
        cpp_ver_26
        compiler_warnings
)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    target_compile_options(simd_01.lib.02_vector_no_fast_math
        PRIVATE
            -Rpass=loop-vectorize
            -Rpass-missed=loop-vectorize
            -Rpass-analysis=loop-vectorize
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(simd_01.lib.02_vector_no_fast_math
        PRIVATE
            -fopt-info-vec-optimized
            -fopt-info-vec-missed
    )
else()
    message(FATAL_ERROR "Unknown compiler detected")
endif()
