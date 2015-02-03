set(AxisLabels_SRCS
    AdjustedCartesianAxis.cpp
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(AxisLabels_SRCS
    mainwindow.ui
)

qt5_add_resources(AxisLabels_SRCS
    BarChart.qrc
)

add_executable(AxisLabels  ${AxisLabels_SRCS})

target_link_libraries(AxisLabels testtools KChart Qt5::Widgets)
