set( KCHARTLIB_VERSION "2.6.89" )

ecm_setup_version(${KCHARTLIB_VERSION}
    VARIABLE_PREFIX KCHART
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kchart_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KChartConfigVersion.cmake"
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Cartesian
    ${CMAKE_CURRENT_SOURCE_DIR}/Cartesian/DiagramFlavors
    ${CMAKE_CURRENT_SOURCE_DIR}/Polar
    ${CMAKE_CURRENT_SOURCE_DIR}/Ternary
)

set( kchart_LIB_SRCS
    KChartMeasure.cpp
    KChartAbstractCoordinatePlane.cpp
    KChartChart.cpp
    KChartWidget.cpp
    KChartAbstractDiagram.cpp
    KChartAbstractDiagram_p.cpp
    KChartAbstractAreaBase.cpp
    KChartAbstractArea.cpp
    KChartTextArea.cpp
    KChartAbstractAreaWidget.cpp
    KChartAbstractAxis.cpp
    KChartAbstractProxyModel.cpp
    KChartAbstractGrid.cpp
    KChartAttributesModel.cpp
    KChartBackgroundAttributes.cpp
    KChartDatasetProxyModel.cpp
    KChartDatasetSelector.cpp
    KChartDataValueAttributes.cpp
    KChartDiagramObserver.cpp
    KChartFrameAttributes.cpp
    KChartGridAttributes.cpp
    KChartRulerAttributes.cpp
    KChartHeaderFooter.cpp
    KChartLayoutItems.cpp
    KChartLegend.cpp
    KChartLineAttributes.cpp
    KChartMarkerAttributes.cpp
    KChartPaintContext.cpp
    KChartPalette.cpp
    KChartPosition.cpp
    KChartRelativePosition.cpp
    KTextDocument.cpp
    KChartTextAttributes.cpp
    KChartAbstractThreeDAttributes.cpp
    KChartThreeDLineAttributes.cpp
    KChartTextLabelCache.cpp
    ChartGraphicsItem.cpp
    ReverseMapper.cpp
    KChartValueTrackerAttributes.cpp
    KChartPrintingParameters.cpp
    KChartModelDataCache_p.cpp
    Cartesian/KChartAbstractCartesianDiagram.cpp
    Cartesian/KChartCartesianCoordinatePlane.cpp
    Cartesian/KChartCartesianAxis.cpp
    Cartesian/KChartCartesianGrid.cpp
    Cartesian/KChartBarDiagram.cpp
    Cartesian/KChartBarDiagram_p.cpp
    Cartesian/KChartThreeDBarAttributes.cpp
    Cartesian/KChartBarAttributes.cpp
    Cartesian/KChartStockBarAttributes.cpp
    Cartesian/KChartStockDiagram.cpp
    Cartesian/KChartStockDiagram_p.cpp
    Cartesian/KChartLineDiagram.cpp
    Cartesian/KChartLineDiagram_p.cpp
    Cartesian/KChartCartesianDiagramDataCompressor_p.cpp
    Cartesian/KChartPlotter.cpp
    Cartesian/KChartPlotter_p.cpp
    Cartesian/KChartPlotterDiagramCompressor.cpp
    Cartesian/KChartLeveyJenningsCoordinatePlane.cpp
    Cartesian/KChartLeveyJenningsDiagram.cpp
    Cartesian/KChartLeveyJenningsDiagram_p.cpp
    Cartesian/KChartLeveyJenningsGrid.cpp
    Cartesian/KChartLeveyJenningsGridAttributes.cpp
    Cartesian/KChartLeveyJenningsAxis.cpp
    Cartesian/PaintingHelpers_p.cpp
    Cartesian/DiagramFlavors/KChartNormalPlotter_p.cpp
    Cartesian/DiagramFlavors/KChartPercentPlotter_p.cpp
    Cartesian/DiagramFlavors/KChartStackedPlotter_p.cpp
    Cartesian/DiagramFlavors/KChartStackedLyingBarDiagram_p.cpp
    Cartesian/DiagramFlavors/KChartStackedLineDiagram_p.cpp
    Cartesian/DiagramFlavors/KChartStackedBarDiagram_p.cpp
    Cartesian/DiagramFlavors/KChartPercentBarDiagram_p.cpp
    Cartesian/DiagramFlavors/KChartPercentLyingBarDiagram_p.cpp
    Cartesian/DiagramFlavors/KChartPercentLineDiagram_p.cpp
    Cartesian/DiagramFlavors/KChartNormalBarDiagram_p.cpp
    Cartesian/DiagramFlavors/KChartNormalLyingBarDiagram_p.cpp
    Cartesian/DiagramFlavors/KChartNormalLineDiagram_p.cpp
    Polar/KChartPolarCoordinatePlane.cpp
    Polar/KChartRadarCoordinatePlane.cpp
    Polar/KChartAbstractPieDiagram.cpp
    Polar/KChartAbstractPolarDiagram.cpp
    Polar/KChartPolarGrid.cpp
    Polar/KChartRadarGrid.cpp
    Polar/KChartPieDiagram.cpp
    Polar/KChartPolarDiagram.cpp
    Polar/KChartRadarDiagram.cpp
    Polar/KChartRingDiagram.cpp
    Polar/KChartPieAttributes.cpp
    Polar/KChartThreeDPieAttributes.cpp
    Ternary/KChartTernaryAxis.cpp
    Ternary/KChartTernaryGrid.cpp
    Ternary/TernaryPoint.cpp
    Ternary/TernaryConstants.cpp
    Ternary/KChartTernaryCoordinatePlane.cpp
    Ternary/KChartAbstractTernaryDiagram.cpp
    Ternary/KChartTernaryPointDiagram.cpp
    Ternary/KChartTernaryLineDiagram.cpp
)

qt5_wrap_ui(kchart_LIB_SRCS
    KChartDatasetSelector.ui
)

qt5_add_resources(kchart_LIB_SRCS
    KChart_LeveyJennings_resources.qrc
)

ecm_create_qm_loader(kchart_LIB_SRCS kchart_qt)

qt_wrap_cpp(KChart kchart_LIB_SRCS KChartEnums.h)

add_library(KChart ${kchart_LIB_SRCS})

# TODO: check if this snippet from .pro file should be ported, otherwise remove file
# linux-*{
#   version_script{
#     QMAKE_LFLAGS += -Wl,--version-script=libkdchart.map
#     TARGETDEPS += libkdchart.map
#   }
# }

generate_export_header( KChart )

target_include_directories(KChart
    INTERFACE "$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}/KChart>"
)

target_link_libraries(KChart
PUBLIC
    Qt5::Widgets
PRIVATE
    Qt5::Svg
)
set_target_properties( KChart PROPERTIES
  VERSION     ${KCHART_VERSION}
  SOVERSION   ${KCHART_SOVERSION}
  EXPORT_NAME "KChart"
)

install( TARGETS KChart
    EXPORT KChartTargets
    ${INSTALL_TARGETS_DEFAULT_ARGS})

set( kchart_LIB_HEADERS
    KChartGlobal.h
    KChartRelativePosition.h
    KChartHeaderFooter.h
    KChartAttributesModel.h
    KChartAbstractAreaBase.h
    KChartAbstractAreaWidget.h
    KChartAbstractProxyModel.h
    KChartLegend.h
    KChartPaintContext.h
    Cartesian/KChartAbstractCartesianDiagram.h
    Cartesian/KChartStockBarAttributes.h
    Cartesian/KChartBarDiagram.h
    Cartesian/KChartThreeDBarAttributes.h
    Cartesian/KChartBarAttributes.h
    Cartesian/KChartLeveyJenningsAxis.h
    Cartesian/KChartCartesianCoordinatePlane.h
    Cartesian/KChartLeveyJenningsDiagram.h
    Cartesian/KChartPlotter.h
    Cartesian/KChartStockDiagram.h
    Cartesian/KChartCartesianAxis.h
    Cartesian/KChartLeveyJenningsGridAttributes.h
    Cartesian/KChartLeveyJenningsCoordinatePlane.h
    Cartesian/KChartLineDiagram.h
    KChartFrameAttributes.h
    KChartLayoutItems.h
    KChartGridAttributes.h
    KChartMarkerAttributes.h
    KChartRulerAttributes.h
    KChartDatasetSelector.h
    KChartDatasetProxyModel.h
    Polar/KChartPolarCoordinatePlane.h
    Polar/KChartRingDiagram.h
    Polar/KChartPieAttributes.h
    Polar/KChartAbstractPolarDiagram.h
    Polar/KChartRadarDiagram.h
    Polar/KChartAbstractPieDiagram.h
    Polar/KChartPolarDiagram.h
    Polar/KChartRadarCoordinatePlane.h
    Polar/KChartThreeDPieAttributes.h
    Polar/KChartPieDiagram.h
    KChartTextArea.h
    KChartAbstractCoordinatePlane.h
    KChartMeasure.h
    KChartValueTrackerAttributes.h
    KChartAbstractArea.h
    KChartDiagramObserver.h
    KChartThreeDLineAttributes.h
    KChartAbstractAxis.h
    KChartAbstractDiagram.h
    KChartPalette.h
    KChartLineAttributes.h
    KChartChart.h
    KChartWidget.h
    KChartAbstractThreeDAttributes.h
    KChartPosition.h
    KChartEnums.h
    Ternary/KChartTernaryPointDiagram.h
    Ternary/KChartTernaryCoordinatePlane.h
    Ternary/KChartTernaryAxis.h
    Ternary/KChartTernaryLineDiagram.h
    Ternary/KChartAbstractTernaryDiagram.h
    KChartBackgroundAttributes.h
    KChartTextAttributes.h
    KChartDataValueAttributes.h
)

# TODO: fix ecm_generate_headers to support camelcase .h files
set( kchart_LIB_FWDHEADERS
    include/KChart
    include/KChartGlobal
    include/KChartRelativePosition
    include/KChartHeaderFooter
    include/KChartAttributesModel
    include/KChartAbstractAreaBase
    include/KChartAbstractAreaWidget
    include/KChartAbstractProxyModel
    include/KChartLegend
    include/KChartPaintContext
    include/KChartAbstractCartesianDiagram
    include/KChartStockBarAttributes
    include/KChartBarDiagram
    include/KChartThreeDBarAttributes
    include/KChartBarAttributes
    include/KChartLeveyJenningsAxis
    include/KChartCartesianCoordinatePlane
    include/KChartLeveyJenningsDiagram
    include/KChartPlotter
    include/KChartStockDiagram
    include/KChartCartesianAxis
    include/KChartLeveyJenningsGridAttributes
    include/KChartLeveyJenningsCoordinatePlane
    include/KChartLineDiagram
    include/KChartFrameAttributes
    include/KChartLayoutItems
    include/KChartGridAttributes
    include/KChartMarkerAttributes
    include/KChartRulerAttributes
    include/KChartDatasetSelector
    include/KChartDatasetProxyModel
    include/KChartPolarCoordinatePlane
    include/KChartRingDiagram
    include/KChartPieAttributes
    include/KChartAbstractPolarDiagram
    include/KChartRadarDiagram
    include/KChartAbstractPieDiagram
    include/KChartPolarDiagram
    include/KChartRadarCoordinatePlane
    include/KChartThreeDPieAttributes
    include/KChartPieDiagram
    include/KChartTextArea
    include/KChartAbstractCoordinatePlane
    include/KChartMeasure
    include/KChartValueTrackerAttributes
    include/KChartAbstractArea
    include/KChartDiagramObserver
    include/KChartThreeDLineAttributes
    include/KChartAbstractAxis
    include/KChartAbstractDiagram
    include/KChartPalette
    include/KChartLineAttributes
    include/KChartChart
    include/KChartWidget
    include/KChartAbstractThreeDAttributes
    include/KChartPosition
    include/KChartEnums
    include/KChartTernaryPointDiagram
    include/KChartTernaryCoordinatePlane
    include/KChartTernaryAxis
    include/KChartTernaryLineDiagram
    include/KChartAbstractTernaryDiagram
    include/KChartBackgroundAttributes
    include/KChartTextAttributes
    include/KChartDataValueAttributes
)

install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/kchart_export.h
            ${kchart_LIB_HEADERS}
            ${kchart_LIB_FWDHEADERS}
        DESTINATION ${INCLUDE_INSTALL_DIR}/KChart
        COMPONENT Devel)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/kchart_version.h
    DESTINATION ${INCLUDE_INSTALL_DIR} COMPONENT Devel)

if(BUILD_QCH)
    ecm_add_qch(
        KChart_QCH
        NAME KChart
        VERSION ${KCHARTLIB_VERSION}
        ORG_DOMAIN org.kde
        SOURCES
            Mainpage.dox
            ${kchart_LIB_HEADERS}
        IMAGE_DIRS "${CMAKE_SOURCE_DIR}/images"
        LINK_QCHS
            Qt5Core_QCH
            Qt5Gui_QCH
            Qt5Widgets_QCH
        BLANK_MACROS
            KCHART_EXPORT
            KCHART_DEPRECATED
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KChart")

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KChart_QCH
        FILE KChartQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KChartQchTargets.cmake\")")
endif()

ecm_configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KChartConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KChartConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/KChartConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/KChartConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

install(EXPORT KChartTargets
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        FILE KChartTargets.cmake)

ecm_generate_pri_file(
    BASE_NAME KChart
    LIB_NAME KChart
    DEPS "widgets svg"
    FILENAME_VAR PRI_FILENAME
    INCLUDE_INSTALL_DIR ${INCLUDE_INSTALL_DIR}/KChart
)

install(FILES ${PRI_FILENAME}
        DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
