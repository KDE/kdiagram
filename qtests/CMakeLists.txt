include(ECMAddTests)

include_directories(
    ${CMAKE_SOURCE_DIR}/examples/tools
    ${CMAKE_SOURCE_DIR}/src/KDChart
    ${CMAKE_SOURCE_DIR}/src/KDChart/include
    ${CMAKE_SOURCE_DIR}/src/KDChart/Cartesian
    ${CMAKE_SOURCE_DIR}/src/KDChart/Cartesian/DiagramFlavors
    ${CMAKE_SOURCE_DIR}/src/KDChart/Polar
    ${CMAKE_SOURCE_DIR}/src/KDChart/Ternary
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
add_subdirectory( PieDiagrams )
add_subdirectory( PolarDiagrams )
add_subdirectory( PolarPlanes )
add_subdirectory( QLayout )
add_subdirectory( RelativePosition )
add_subdirectory( WidgetElementOwnership )
