# KGantt examples
add_subdirectory(Gantt)

# KChart examples
include_directories(
    ${CMAKE_SOURCE_DIR}/examples/tools
    ${CMAKE_BINARY_DIR}/examples/tools
    ${CMAKE_SOURCE_DIR}/src/KChart
    ${CMAKE_SOURCE_DIR}/src/KChart/include
    ${CMAKE_SOURCE_DIR}/src/KChart/Cartesian
    ${CMAKE_SOURCE_DIR}/src/KChart/Cartesian/DiagramFlavors
    ${CMAKE_SOURCE_DIR}/src/KChart/Polar
    ${CMAKE_SOURCE_DIR}/src/KChart/Ternary
)
remove_definitions(
    -DQT_NO_KEYWORDS
    -DQT_NO_SIGNALS_SLOTS_KEYWORDS
    -DQT_NO_CAST_FROM_ASCII
)

add_subdirectory(tools)
add_subdirectory(demo)

add_subdirectory(Axis)
add_subdirectory(Background)
add_subdirectory(Bars)
add_subdirectory(DataValueTexts)
add_subdirectory(DrawIntoPainter)
add_subdirectory(EmptyValues)
add_subdirectory(Grids)
add_subdirectory(HeadersFooters)
add_subdirectory(Legends)
add_subdirectory(LeveyJennings)
add_subdirectory(Lines)
add_subdirectory(ModelView)
add_subdirectory(NoValues)
add_subdirectory(Pie)
add_subdirectory(Plane)
add_subdirectory(Plotter)
add_subdirectory(Polar)
add_subdirectory(RealTime)
add_subdirectory(SharedAbscissa)
if (Qt5Sql_FOUND)
    add_subdirectory(Sql)
endif()
add_subdirectory(Stock)
add_subdirectory(TernaryCharts)
add_subdirectory(Widget)
add_subdirectory(Zoom)
add_subdirectory(Radar)
