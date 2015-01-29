set( KGANTTLIB_VERSION "2.6.0" )

ecm_setup_version(${KGANTTLIB_VERSION}
    VARIABLE_PREFIX KGANTT
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KGanttConfigVersion.cmake"
)

if(NOT BUILD_TESTING)
    add_definitions(-DKDAB_NO_UNIT_TESTS)
endif()

set( kgantt_LIB_SRCS
    kganttglobal.cpp
    kganttview.cpp
    kganttstyleoptionganttitem.cpp
    kganttgraphicsview.cpp
    kganttabstractrowcontroller.cpp
    kgantttreeviewrowcontroller.cpp
    kganttlistviewrowcontroller.cpp
    kganttgraphicsscene.cpp
    kganttgraphicsitem.cpp
    kganttconstraint.cpp
    kganttconstraintproxy.cpp
    kganttconstraintgraphicsitem.cpp
    kganttitemdelegate.cpp
    kganttforwardingproxymodel.cpp
    kganttsummaryhandlingproxymodel.cpp
    kganttproxymodel.cpp
    kganttconstraintmodel.cpp
    kganttabstractgrid.cpp
    kganttdatetimegrid.cpp
    kganttlegend.cpp
    unittest/test.cpp
    unittest/testregistry.cpp
)

add_library( KGantt SHARED ${kgantt_LIB_SRCS} )

generate_export_header( KGantt )

target_include_directories(KGantt
    INTERFACE "$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}/KGantt>"
)

target_link_libraries( KGantt LINK_PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::PrintSupport
)

set_target_properties( KGantt PROPERTIES
  VERSION     ${KGANTT_VERSION}
  SOVERSION   ${KGANTT_SOVERSION}
  EXPORT_NAME "KGantt"
)

install( TARGETS KGantt
    EXPORT KGanttTargets
    ${INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(kgantt_LIB_HEADERS
    HEADER_NAMES
    KGanttGlobal
    KGanttView
    KGanttListViewRowController
    KGanttStyleOptionGanttItem
    KGanttGraphicsView
    KGanttAbstractRowController
    KGanttTreeviewRowController
    KGanttListviewRowController
    KGanttGraphicsScene
    KGanttGraphicsItem
    KGanttConstraint
    KGanttConstraintProxy
    KGanttConstraintGraphicsItem
    KGanttItemDelegate
    KGanttForwardingproxyModel
    KGanttSummaryHandlingProxyModel
    KGanttProxymodel
    KGanttConstraintModel
    KGanttAbstractGrid
    KGanttDateTimeGrid
    KGanttLegend

    REQUIRED_HEADERS kgantt_LIB_HEADERS
)

install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/kgantt_export.h
            ${kgantt_LIB_HEADERS}
        DESTINATION ${INCLUDE_INSTALL_DIR}/KGantt
        COMPONENT Devel)

# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KGantt")

ecm_configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KGanttConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KGanttConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/KGanttConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/KGanttConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

install(EXPORT KGanttTargets
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        FILE KGanttTargets.cmake)

ecm_generate_pri_file(
    BASE_NAME KGantt
    LIB_NAME KGantt
    DEPS "widgets printsupport"
    FILENAME_VAR PRI_FILENAME
    INCLUDE_INSTALL_DIR ${INCLUDE_INSTALL_DIR}/KGantt
)

install(FILES ${PRI_FILENAME}
        DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
