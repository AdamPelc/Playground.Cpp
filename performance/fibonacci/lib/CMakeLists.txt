add_library(fibonacci STATIC)

target_include_directories(fibonacci
PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(fibonacci.test)

target_link_libraries(fibonacci.test
PRIVATE
        fibonacci
        gtest
        gtest_main
)

add_subdirectory(src)
