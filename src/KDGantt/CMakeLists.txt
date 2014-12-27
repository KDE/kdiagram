ecm_setup_version(${KDEKDCHARTLIBS_VERSION}
    VARIABLE_PREFIX KDEKDGANTT
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KDEKDGanttConfigVersion.cmake"
)

add_definitions(-DKDAB_NO_UNIT_TESTS)

set( kdgantt_LIB_SRCS
    kdganttglobal.cpp
    kdganttview.cpp
    kdganttstyleoptionganttitem.cpp
    kdganttgraphicsview.cpp
    kdganttabstractrowcontroller.cpp
    kdgantttreeviewrowcontroller.cpp
    kdganttlistviewrowcontroller.cpp
    kdganttgraphicsscene.cpp
    kdganttgraphicsitem.cpp
    kdganttconstraint.cpp
    kdganttconstraintproxy.cpp
    kdganttconstraintgraphicsitem.cpp
    kdganttitemdelegate.cpp
    kdganttforwardingproxymodel.cpp
    kdganttsummaryhandlingproxymodel.cpp
    kdganttproxymodel.cpp
    kdganttconstraintmodel.cpp
    kdganttabstractgrid.cpp
    kdganttdatetimegrid.cpp
    kdganttlegend.cpp
)

add_library( kde-kdgantt SHARED ${kdgantt_LIB_SRCS} )

generate_export_header( kde-kdgantt )

add_library( KDEKDGantt ALIAS kde-kdgantt )

target_include_directories(kde-kdgantt
    INTERFACE "$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}/KDEKDGantt>"
)

target_link_libraries( kde-kdgantt LINK_PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::PrintSupport
)

set_target_properties( kde-kdgantt PROPERTIES
  VERSION     ${KDEKDGANTT_VERSION}
  SOVERSION   ${KDEKDGANTT_SOVERSION}
  EXPORT_NAME "KDEKDGantt"
)

install( TARGETS kde-kdgantt
    EXPORT KDEKDGanttTargets
    ${INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(kdgantt_LIB_HEADERS
    HEADER_NAMES
    KDGanttView
    KDGanttStyleOptionGanttItem
    KDGanttGraphicsView
    KDGanttAbstractRowController
    KDGanttTreeviewRowController
    KDGanttListviewRowController
    KDGanttGraphicsScene
    KDGanttGraphicsItem
    KDGanttConstraint
    KDGanttConstraintProxy
    KDGanttConstraintGraphicsItem
    KDGanttItemDelegate
    KDGanttForwardingproxyModel
    KDGanttSummaryHandlingProxyModel
    KDGanttProxymodel
    KDGanttConstraintModel
    KDGanttAbstractGrid
    KDGanttDateTimeGrid
    KDGanttLegend

    REQUIRED_HEADERS kdgantt_LIB_HEADERS
)

install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/kde-kdgantt_export.h
            ${kdgantt_LIB_HEADERS}
        DESTINATION ${INCLUDE_INSTALL_DIR}/KDEKDGantt
        COMPONENT Devel)

# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KDEKDGantt")

ecm_configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KDEKDGanttConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KDEKDGanttConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/KDEKDGanttConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/KDEKDGanttConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

install(EXPORT KDEKDGanttTargets
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        FILE KDEKDGanttTargets.cmake)
