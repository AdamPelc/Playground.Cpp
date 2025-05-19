########################################################################################################################
# Queue | Test
########################################################################################################################
add_executable(queue.test)
target_link_libraries(queue.test
PRIVATE
    compiler_warnings
    compiler_features
    queue
    GTest::gtest
    GTest::gtest_main
)
target_sources(queue.test
PRIVATE
    spsc_queue.test.cpp
)
