set(AxisChart_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(AxisChart_SRCS
    mainwindow.ui
)

qt5_add_resources(AxisChart_SRCS
    BarChart.qrc
)

add_executable(AxisChart  ${AxisChart_SRCS})

target_link_libraries(AxisChart testtools KChart Qt5::Widgets)
