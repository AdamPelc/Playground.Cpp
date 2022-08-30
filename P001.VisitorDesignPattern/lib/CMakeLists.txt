add_library(${PROJECT_NAME}.Lib)

target_include_directories(${PROJECT_NAME}.Lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(${PROJECT_NAME}.Lib
    PRIVATE
        -std=c++20
)

add_subdirectory(Animal)
add_subdirectory(Serialize)
