include_directories(
    ${CMAKE_SOURCE_DIR}/src/KDChart
)

add_definitions(-DKDAB_NO_UNIT_TESTS -DKDGANTT_SHAREDLIB -DKDGANTT_BUILD_KDGANTT_LIB)

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

target_link_libraries( kde-kdgantt LINK_PRIVATE
    kde-kdchart
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::PrintSupport
)

set_target_properties( kde-kdgantt PROPERTIES
  VERSION     ${KDEKDCHARTLIBS_LIB_VERSION}
  SOVERSION   ${KDEKDCHARTLIBS_LIB_SOVERSION}
)

install( TARGETS kde-kdgantt ${INSTALL_TARGETS_DEFAULT_ARGS} )

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
