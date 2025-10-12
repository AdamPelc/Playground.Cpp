project(P001.VisitorDesignPattern)

add_executable(${PROJECT_NAME}
    main.cpp
)

add_subdirectory(lib)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_NAME}.Lib
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -std=c++20
)
