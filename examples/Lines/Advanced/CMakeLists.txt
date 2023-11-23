set(LinesAdvanced_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_wrap_ui(LinesAdvanced_SRCS
    mainwindow.ui
)

qt_add_resources(LinesAdvanced_SRCS
    LineChart.qrc
)

add_executable(LinesAdvanced  ${LinesAdvanced_SRCS})

target_link_libraries(LinesAdvanced testtools KChartQt6 Qt::Widgets)
