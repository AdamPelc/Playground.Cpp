add_library(simd_01.lib.01_no_vector STATIC)
target_sources(simd_01.lib.01_no_vector
    PRIVATE
        01_no_vector.cpp
)
target_include_directories(simd_01.lib.01_no_vector
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(simd_01.lib.01_no_vector
    PUBLIC
        simd_01.lib.common
    PRIVATE
        cpp_ver_26
        compiler_warnings
)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    target_compile_options(simd_01.lib.01_no_vector
        PRIVATE
            -Rpass=loop-vectorize
            -Rpass-missed=loop-vectorize
            -Rpass-analysis=loop-vectorize
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(simd_01.lib.01_no_vector
        PRIVATE
            -fopt-info-vec-optimized
            -fopt-info-vec-missed
    )
else()
    message(FATAL_ERROR "Unknown compiler detected")
endif()
