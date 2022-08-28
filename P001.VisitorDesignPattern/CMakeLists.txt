project(P001.VisitorDesignPattern)

add_executable(${PROJECT_NAME}
    main.cpp
)

add_subdirectory(lib)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_NAME}.Lib
)
