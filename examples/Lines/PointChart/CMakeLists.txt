set(PointChart_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_wrap_ui(PointChart_SRCS
    mainwindow.ui
)

qt_add_resources(PointChart_SRCS
    LineChart.qrc
)

add_executable(PointChart  ${PointChart_SRCS})

target_link_libraries(PointChart testtools KChart6 Qt::Widgets)
