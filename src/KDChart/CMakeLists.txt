include_directories(
    ${CMAKE_SOURCE_DIR}/kdablibfakes/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Cartesian
    ${CMAKE_CURRENT_SOURCE_DIR}/Cartesian/DiagramFlavors
    ${CMAKE_CURRENT_SOURCE_DIR}/Polar
    ${CMAKE_CURRENT_SOURCE_DIR}/Ternary
)

add_definitions(-DKDCHART_BUILD_KDCHART_LIB)

set( kdchart_LIB_SRCS
    KDChartMeasure.cpp
    KDChartAbstractCoordinatePlane.cpp
    KDChartChart.cpp
    KDChartWidget.cpp
    KDChartAbstractDiagram.cpp
    KDChartAbstractDiagram_p.cpp
    KDChartAbstractAreaBase.cpp
    KDChartAbstractArea.cpp
    KDChartTextArea.cpp
    KDChartAbstractAreaWidget.cpp
    KDChartAbstractAxis.cpp
    KDChartAbstractProxyModel.cpp
    KDChartAbstractGrid.cpp
    KDChartAttributesModel.cpp
    KDChartBackgroundAttributes.cpp
    KDChartDatasetProxyModel.cpp
    KDChartDatasetSelector.cpp
    KDChartDataValueAttributes.cpp
    KDChartDiagramObserver.cpp
    KDChartFrameAttributes.cpp
    KDChartGridAttributes.cpp
    KDChartRulerAttributes.cpp
    KDChartHeaderFooter.cpp
    KDChartLayoutItems.cpp
    KDChartLegend.cpp
    KDChartLineAttributes.cpp
    KDChartMarkerAttributes.cpp
    KDChartPaintContext.cpp
    KDChartPalette.cpp
    KDChartPosition.cpp
    KDChartRelativePosition.cpp
    KDTextDocument.cpp
    KDChartTextAttributes.cpp
    KDChartAbstractThreeDAttributes.cpp
    KDChartThreeDLineAttributes.cpp
    KDChartTextLabelCache.cpp
    ChartGraphicsItem.cpp
    ReverseMapper.cpp
    KDChartValueTrackerAttributes.cpp
    KDChartPrintingParameters.cpp
    KDChartModelDataCache_p.cpp
    Cartesian/KDChartAbstractCartesianDiagram.cpp
    Cartesian/KDChartCartesianCoordinatePlane.cpp
    Cartesian/KDChartCartesianAxis.cpp
    Cartesian/KDChartCartesianGrid.cpp
    Cartesian/KDChartBarDiagram.cpp
    Cartesian/KDChartBarDiagram_p.cpp
    Cartesian/KDChartThreeDBarAttributes.cpp
    Cartesian/KDChartBarAttributes.cpp
    Cartesian/KDChartStockBarAttributes.cpp
    Cartesian/KDChartStockDiagram.cpp
    Cartesian/KDChartStockDiagram_p.cpp
    Cartesian/KDChartLineDiagram.cpp
    Cartesian/KDChartLineDiagram_p.cpp
    Cartesian/KDChartCartesianDiagramDataCompressor_p.cpp
    Cartesian/KDChartPlotter.cpp
    Cartesian/KDChartPlotter_p.cpp
    Cartesian/KDChartPlotterDiagramCompressor.cpp
    Cartesian/KDChartLeveyJenningsCoordinatePlane.cpp
    Cartesian/KDChartLeveyJenningsDiagram.cpp
    Cartesian/KDChartLeveyJenningsDiagram_p.cpp
    Cartesian/KDChartLeveyJenningsGrid.cpp
    Cartesian/KDChartLeveyJenningsGridAttributes.cpp
    Cartesian/KDChartLeveyJenningsAxis.cpp
    Cartesian/PaintingHelpers_p.cpp
    Cartesian/DiagramFlavors/KDChartNormalPlotter_p.cpp
    Cartesian/DiagramFlavors/KDChartPercentPlotter_p.cpp
    Cartesian/DiagramFlavors/KDChartStackedLyingBarDiagram_p.cpp
    Cartesian/DiagramFlavors/KDChartStackedLineDiagram_p.cpp
    Cartesian/DiagramFlavors/KDChartStackedBarDiagram_p.cpp
    Cartesian/DiagramFlavors/KDChartPercentBarDiagram_p.cpp
    Cartesian/DiagramFlavors/KDChartPercentLyingBarDiagram_p.cpp
    Cartesian/DiagramFlavors/KDChartPercentLineDiagram_p.cpp
    Cartesian/DiagramFlavors/KDChartNormalBarDiagram_p.cpp
    Cartesian/DiagramFlavors/KDChartNormalLyingBarDiagram_p.cpp
    Cartesian/DiagramFlavors/KDChartNormalLineDiagram_p.cpp
    Polar/KDChartPolarCoordinatePlane.cpp
    Polar/KDChartRadarCoordinatePlane.cpp
    Polar/KDChartAbstractPieDiagram.cpp
    Polar/KDChartAbstractPolarDiagram.cpp
    Polar/KDChartPolarGrid.cpp
    Polar/KDChartRadarGrid.cpp
    Polar/KDChartPieDiagram.cpp
    Polar/KDChartPolarDiagram.cpp
    Polar/KDChartRadarDiagram.cpp
    Polar/KDChartRingDiagram.cpp
    Polar/KDChartPieAttributes.cpp
    Polar/KDChartThreeDPieAttributes.cpp
    Ternary/KDChartTernaryAxis.cpp
    Ternary/KDChartTernaryGrid.cpp
    Ternary/TernaryPoint.cpp
    Ternary/TernaryConstants.cpp
    Ternary/KDChartTernaryCoordinatePlane.cpp
    Ternary/KDChartAbstractTernaryDiagram.cpp
    Ternary/KDChartTernaryPointDiagram.cpp
    Ternary/KDChartTernaryLineDiagram.cpp
)

qt5_wrap_ui(kdchart_LIB_SRCS
    KDChartDatasetSelector.ui
)

qt_wrap_cpp(kde-kdchart kdchart_LIB_SRCS KDChartEnums.h)

add_library(kde-kdchart SHARED ${kdchart_LIB_SRCS})

generate_export_header( kde-kdchart )

target_link_libraries(kde-kdchart LINK_PRIVATE
    Qt5::Svg
    Qt5::Widgets
    Qt5::Core
)
set_target_properties( kde-kdchart PROPERTIES
  VERSION     ${KDEKDCHARTLIBS_LIB_VERSION}
  SOVERSION   ${KDEKDCHARTLIBS_LIB_SOVERSION}
)

install( TARGETS kde-kdchart ${INSTALL_TARGETS_DEFAULT_ARGS} )
