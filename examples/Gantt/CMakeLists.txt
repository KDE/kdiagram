include_directories(
    ${CMAKE_SOURCE_DIR}/src/KDGantt
    ${CMAKE_BINARY_DIR}/src/KDGantt
)

remove_definitions(
    -DQT_NO_KEYWORDS
    -DQT_NO_SIGNALS_SLOTS_KEYWORDS
    -DQT_NO_CAST_FROM_ASCII
)

add_subdirectory(legend_example)
add_subdirectory(project)
