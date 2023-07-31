add_executable(CustomIterator.Vector.UT
    Vector.Iterator.UT.cpp
    Vector.UT.cpp
)

target_link_libraries(CustomIterator.Vector.UT
    PRIVATE
    GTest::gtest
    GTest::gtest_main
    CustomIterator.Vector
)
add_test(
    NAME CustomIterator.Vector.UT
    COMMAND CustomIterator.Vector.UT
)
