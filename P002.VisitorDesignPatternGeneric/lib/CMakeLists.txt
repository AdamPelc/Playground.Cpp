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
target_link_libraries(${PROJECT_NAME}.Lib
    PUBLIC
        P002.Animal
)

add_subdirectory(Serialize)
