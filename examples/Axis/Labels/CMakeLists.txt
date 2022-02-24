set(AxisLabels_SRCS
    AdjustedCartesianAxis.cpp
    mainwindow.cpp
    AdjustedCartesianAxis.h
    mainwindow.h
    main.cpp
)

qt_wrap_ui(AxisLabels_SRCS
    mainwindow.ui
)

qt_add_resources(AxisLabels_SRCS
    BarChart.qrc
)

add_executable(AxisLabels  ${AxisLabels_SRCS})

target_link_libraries(AxisLabels testtools KChart Qt::Widgets)
