add_library(maximum_flow-Ford_Fulkerson_DFS STATIC)
target_sources(maximum_flow-Ford_Fulkerson_DFS
PRIVATE
    maximum_flow.cpp
)
target_link_libraries(maximum_flow-Ford_Fulkerson_DFS
PRIVATE
    fmt::fmt
)

add_executable(maximum_flow-Ford_Fulkerson_DFS.Test)
target_sources(maximum_flow-Ford_Fulkerson_DFS.Test
PRIVATE
    main.test.cpp
)
target_link_libraries(maximum_flow-Ford_Fulkerson_DFS.Test
PRIVATE
    maximum_flow-Ford_Fulkerson_DFS
    gtest
    gtest_main
)