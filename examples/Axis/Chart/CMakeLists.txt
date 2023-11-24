set(AxisChart_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_wrap_ui(AxisChart_SRCS
    mainwindow.ui
)

qt_add_resources(AxisChart_SRCS
    BarChart.qrc
)

add_executable(AxisChart  ${AxisChart_SRCS})

target_link_libraries(AxisChart testtools KChart6 Qt::Widgets)
