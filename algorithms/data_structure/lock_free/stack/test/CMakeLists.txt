add_executable(lf_stack.test)

target_sources(lf_stack.test
PRIVATE
    lf_stack.test.cpp
)

target_link_libraries(lf_stack.test
PRIVATE
    lf_stack
    compiler_warnings
    compiler_features
    thread_sanitizer
    gtest
    gtest_main
)
