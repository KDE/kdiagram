ecm_setup_version(${KDEKDCHARTLIBS_VERSION}
    VARIABLE_PREFIX KDEKDCHART
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KDEKDChartConfigVersion.cmake"
)

include_directories(
    ${CMAKE_SOURCE_DIR}/kdablibfakes/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Cartesian
    ${CMAKE_CURRENT_SOURCE_DIR}/Cartesian/DiagramFlavors
    ${CMAKE_CURRENT_SOURCE_DIR}/Polar
    ${CMAKE_CURRENT_SOURCE_DIR}/Ternary
)

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
    Cartesian/DiagramFlavors/KDChartStackedPlotter_p.cpp
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
  VERSION     ${KDEKDCHART_VERSION}
  SOVERSION   ${KDEKDCHART_SOVERSION}
)

install( TARGETS kde-kdchart
    EXPORT KDEKDChartTargets
    ${INSTALL_TARGETS_DEFAULT_ARGS})

set( kdchart_LIB_HEADERS
    KDChartGlobal.h
    KDChartRelativePosition.h
    KDChartHeaderFooter.h
    KDChartAttributesModel.h
    KDChartAbstractAreaBase.h
    KDChartAbstractAreaWidget.h
    KDChartAbstractProxyModel.h
    KDChartLegend.h
    KDChartPaintContext.h
    Cartesian/KDChartAbstractCartesianDiagram.h
    Cartesian/KDChartStockBarAttributes.h
    Cartesian/KDChartBarDiagram.h
    Cartesian/KDChartThreeDBarAttributes.h
    Cartesian/KDChartBarAttributes.h
    Cartesian/KDChartLeveyJenningsAxis.h
    Cartesian/KDChartCartesianCoordinatePlane.h
    Cartesian/KDChartLeveyJenningsDiagram.h
    Cartesian/KDChartPlotter.h
    Cartesian/KDChartStockDiagram.h
    Cartesian/KDChartCartesianAxis.h
    Cartesian/KDChartLeveyJenningsGridAttributes.h
    Cartesian/KDChartLeveyJenningsCoordinatePlane.h
    Cartesian/KDChartLineDiagram.h
    KDChartFrameAttributes.h
    KDChartLayoutItems.h
    KDChartGridAttributes.h
    KDChartMarkerAttributes.h
    KDChartRulerAttributes.h
    KDChartDatasetSelector.h
    KDChartDatasetProxyModel.h
    Polar/KDChartPolarCoordinatePlane.h
    Polar/KDChartRingDiagram.h
    Polar/KDChartPieAttributes.h
    Polar/KDChartAbstractPolarDiagram.h
    Polar/KDChartRadarDiagram.h
    Polar/KDChartAbstractPieDiagram.h
    Polar/KDChartPolarDiagram.h
    Polar/KDChartRadarCoordinatePlane.h
    Polar/KDChartThreeDPieAttributes.h
    Polar/KDChartPieDiagram.h
    KDChartTextArea.h
    KDChartAbstractCoordinatePlane.h
    KDChartMeasure.h
    KDChartValueTrackerAttributes.h
    KDChartAbstractArea.h
    KDChartDiagramObserver.h
    KDChartThreeDLineAttributes.h
    KDChartAbstractAxis.h
    KDChartAbstractDiagram.h
    KDChartPalette.h
    KDChartLineAttributes.h
    KDChartChart.h
    KDChartWidget.h
    KDChartAbstractThreeDAttributes.h
    KDChartPosition.h
    KDChartEnums.h
    Ternary/KDChartTernaryPointDiagram.h
    Ternary/KDChartTernaryCoordinatePlane.h
    Ternary/KDChartTernaryAxis.h
    Ternary/KDChartTernaryLineDiagram.h
    Ternary/KDChartAbstractTernaryDiagram.h
    KDChartBackgroundAttributes.h
    KDChartTextAttributes.h
    KDChartDataValueAttributes.h
)

# TODO: fix ecm_generate_headers to support camelcase .h files
set( kdchart_LIB_FWDHEADERS
    include/KDChart
    include/KDChartGlobal
    include/KDChartRelativePosition
    include/KDChartHeaderFooter
    include/KDChartAttributesModel
    include/KDChartAbstractAreaBase
    include/KDChartAbstractAreaWidget
    include/KDChartAbstractProxyModel
    include/KDChartLegend
    include/KDChartPaintContext
    include/KDChartAbstractCartesianDiagram
    include/KDChartStockBarAttributes
    include/KDChartBarDiagram
    include/KDChartThreeDBarAttributes
    include/KDChartBarAttributes
    include/KDChartLeveyJenningsAxis
    include/KDChartCartesianCoordinatePlane
    include/KDChartLeveyJenningsDiagram
    include/KDChartPlotter
    include/KDChartStockDiagram
    include/KDChartCartesianAxis
    include/KDChartLeveyJenningsGridAttributes
    include/KDChartLeveyJenningsCoordinatePlane
    include/KDChartLineDiagram
    include/KDChartFrameAttributes
    include/KDChartLayoutItems
    include/KDChartGridAttributes
    include/KDChartMarkerAttributes
    include/KDChartRulerAttributes
    include/KDChartDatasetSelector
    include/KDChartDatasetProxyModel
    include/KDChartPolarCoordinatePlane
    include/KDChartRingDiagram
    include/KDChartPieAttributes
    include/KDChartAbstractPolarDiagram
    include/KDChartRadarDiagram
    include/KDChartAbstractPieDiagram
    include/KDChartPolarDiagram
    include/KDChartRadarCoordinatePlane
    include/KDChartThreeDPieAttributes
    include/KDChartPieDiagram
    include/KDChartTextArea
    include/KDChartAbstractCoordinatePlane
    include/KDChartMeasure
    include/KDChartValueTrackerAttributes
    include/KDChartAbstractArea
    include/KDChartDiagramObserver
    include/KDChartThreeDLineAttributes
    include/KDChartAbstractAxis
    include/KDChartAbstractDiagram
    include/KDChartPalette
    include/KDChartLineAttributes
    include/KDChartChart
    include/KDChartWidget
    include/KDChartAbstractThreeDAttributes
    include/KDChartPosition
    include/KDChartEnums
    include/KDChartTernaryPointDiagram
    include/KDChartTernaryCoordinatePlane
    include/KDChartTernaryAxis
    include/KDChartTernaryLineDiagram
    include/KDChartAbstractTernaryDiagram
    include/KDChartBackgroundAttributes
    include/KDChartTextAttributes
    include/KDChartDataValueAttributes
)

install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/kde-kdchart_export.h
            ${kdchart_LIB_HEADERS}
            ${kdchart_LIB_FWDHEADERS}
        DESTINATION ${INCLUDE_INSTALL_DIR}
        COMPONENT Devel)

# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KDEKDChart")

ecm_configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KDEKDChartConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KDEKDChartConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/KDEKDChartConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/KDEKDChartConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

install(EXPORT KDEKDChartTargets
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        FILE KDEKDChartTargets.cmake)
