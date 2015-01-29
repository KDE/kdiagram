ecm_setup_version(${KDEKDCHARTLIBS_VERSION}
    VARIABLE_PREFIX KDEKDGANTT
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KDEKDGanttConfigVersion.cmake"
)

if(NOT BUILD_TESTING)
    add_definitions(-DKDAB_NO_UNIT_TESTS)
endif()

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
    unittest/test.cpp
    unittest/testregistry.cpp
)

add_library( KDEKDGantt SHARED ${kdgantt_LIB_SRCS} )

generate_export_header( KDEKDGantt )

target_include_directories(KDEKDGantt
    INTERFACE "$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}/KDEKDGantt>"
)

target_link_libraries( KDEKDGantt LINK_PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::PrintSupport
)

set_target_properties( KDEKDGantt PROPERTIES
  VERSION     ${KDEKDGANTT_VERSION}
  SOVERSION   ${KDEKDGANTT_SOVERSION}
  EXPORT_NAME "KDEKDGantt"
)

install( TARGETS KDEKDGantt
    EXPORT KDEKDGanttTargets
    ${INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(kdgantt_LIB_HEADERS
    HEADER_NAMES
    KDGanttGlobal
    KDGanttView
    KDGanttListViewRowController
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
            ${CMAKE_CURRENT_BINARY_DIR}/kdekdgantt_export.h
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

ecm_generate_pri_file(
    BASE_NAME KDEKDGantt
    LIB_NAME KDEKDGantt
    DEPS "widgets printsupport"
    FILENAME_VAR PRI_FILENAME
    INCLUDE_INSTALL_DIR ${INCLUDE_INSTALL_DIR}/KDEKDGantt
)

install(FILES ${PRI_FILENAME}
        DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
