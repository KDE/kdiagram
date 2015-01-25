include_directories(
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

# Disabled for Windows cause compiling the RootIndex and DelayedData samples
# with mingw or nmake results in a Q_ASSERT in qmake (cause QList.first()
# is used while the QList is empty, removing the required
# OBJECTS_DIR from the RootIndex.pro fixes it) if qmake was
# compiled with debug enabled or in a crash if not.
if(NOT WIN32)
    add_subdirectory( DelayedData )
    add_subdirectory( RootIndex )
endif()
