
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

add_subdirectory( AttributesModel )
add_subdirectory( AxisOwnership )
add_subdirectory( BarDiagrams )
add_subdirectory( CartesianDiagramDataCompressor )
add_subdirectory( CartesianPlanes )
add_subdirectory( ChartElementOwnership )
add_subdirectory( Cloning )
add_subdirectory( DrawIntoPainter )
add_subdirectory( Legends )
add_subdirectory( LineDiagrams )
add_subdirectory( Measure )
add_subdirectory( Palette )
add_subdirectory( ParamVsParam )
add_subdirectory( PolarDiagrams )
add_subdirectory( PieDiagrams )
add_subdirectory( RingDiagrams )
add_subdirectory( RadarDiagrams )
add_subdirectory( PolarPlanes )
add_subdirectory( QLayout )
add_subdirectory( RelativePosition )
add_subdirectory( WidgetElementOwnership )
