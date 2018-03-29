set( KGANTTLIB_VERSION "2.6.89" )

ecm_setup_version(${KGANTTLIB_VERSION}
    VARIABLE_PREFIX KGANTT
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kgantt_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KGanttConfigVersion.cmake"
)

if(BUILD_TESTING)
    if(Qt5Test_FOUND)
        add_subdirectory(test)
    endif()
endif()

# TODO: remove this, code should be built the same with and without unit tests
# those KGantt unit tests which are enabled in the sources should be moved into own files
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

if(CMAKE_COMPILER_IS_GNUCXX)
# remove once c++11-only
# avoid warning about deprecated std::auto_ptr
set_source_files_properties(unittest/testregistry.cpp
    PROPERTIES
        COMPILE_FLAGS "-Wno-deprecated-declarations"
)
endif(CMAKE_COMPILER_IS_GNUCXX)

ecm_create_qm_loader(kgantt_LIB_SRCS kgantt_qt)

add_library( KGantt ${kgantt_LIB_SRCS} )

generate_export_header( KGantt )

target_include_directories(KGantt
    INTERFACE "$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}/KGantt>"
)

target_link_libraries( KGantt
PUBLIC
    Qt5::Widgets
PRIVATE
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
    KGanttStyleOptionGanttItem
    KGanttGraphicsView
    KGanttAbstractRowController
    KGanttTreeViewRowController
    KGanttListViewRowController
    KGanttGraphicsScene
    KGanttGraphicsItem
    KGanttConstraint
    KGanttConstraintProxy
    KGanttConstraintGraphicsItem
    KGanttItemDelegate
    KGanttForwardingProxyModel
    KGanttSummaryHandlingProxyModel
    KGanttProxyModel
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

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/kgantt_version.h
    DESTINATION ${INCLUDE_INSTALL_DIR} COMPONENT Devel)

if(BUILD_QCH)
    ecm_add_qch(
        KGantt_QCH
        NAME KGantt
        VERSION ${KGANTTLIB_VERSION}
        ORG_DOMAIN org.kde
        SOURCES
            Mainpage.dox
            ${kgantt_LIB_HEADERS}
            ${kgantt_LIB_SRCS}
        LINK_QCHS
            Qt5Core_QCH
            Qt5Gui_QCH
            Qt5Widgets_QCH
        BLANK_MACROS
            KGANTT_EXPORT
            KGANTT_DEPRECATED
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

# create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KGantt")

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KGantt_QCH
        FILE KGanttQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KGanttQchTargets.cmake\")")
endif()

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
