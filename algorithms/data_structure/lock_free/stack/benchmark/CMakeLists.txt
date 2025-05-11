add_executable(lf_stack.benchmark)

target_sources(lf_stack.benchmark
PRIVATE
    lf_stack.benchmark.cpp
    stack_lock_guard.benchmark.cpp
)

target_link_libraries(lf_stack.benchmark
PRIVATE
    lf_stack
    benchmark::benchmark
    compiler_features
    compiler_warnings
    atomic
)
