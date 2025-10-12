add_executable(fibonacci.bench)

target_sources(fibonacci.bench
PRIVATE
        fibonacci.bench.cpp
)

target_link_libraries(fibonacci.bench
PRIVATE
        fibonacci
        benchmark::benchmark
)
