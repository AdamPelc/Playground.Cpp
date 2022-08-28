add_library(${PROJECT_NAME}.Lib)

target_include_directories(${PROJECT_NAME}.Lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(Animal)
