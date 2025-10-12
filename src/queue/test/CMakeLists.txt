########################################################################################################################
# Queue | Test
########################################################################################################################
add_executable(queue.test)
target_sources(queue.test
PRIVATE
    spsc_queue.test.cpp
)
target_link_libraries(queue.test
PRIVATE
    compiler_warnings
    cpp_ver_23
    queue
    GTest::gtest
    GTest::gtest_main
    $<$<BOOL:${ENABLE_TSAN}>:tsan>
)
