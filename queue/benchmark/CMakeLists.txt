########################################################################################################################
# Queue | Benchmark
########################################################################################################################
add_executable(queue.benchmark)
target_link_libraries(queue.benchmark
PRIVATE
    compiler_warnings
    compiler_features
    queue
    benchmark::benchmark
)
target_sources(queue.benchmark
PRIVATE
    spsc_queue.benchmark.cpp
)
