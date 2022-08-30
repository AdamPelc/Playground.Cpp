project(P002.Animal)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -std=c++20
)

add_subdirectory(sources)
