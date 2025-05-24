########################################################################################################################
# Queue | Benchmark
########################################################################################################################
add_executable(queue.benchmark)
target_link_libraries(queue.benchmark
PRIVATE
    compiler_warnings
    cpp_ver_23
    queue
    benchmark::benchmark
    $<$<BOOL:${ENABLE_TSAN}>:tsan>
)
target_sources(queue.benchmark
PRIVATE
    spsc_queue.benchmark.cpp
)
