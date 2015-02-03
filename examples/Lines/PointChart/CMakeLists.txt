set(PointChart_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(PointChart_SRCS
    mainwindow.ui
)

qt5_add_resources(PointChart_SRCS
    LineChart.qrc
)

add_executable(PointChart  ${PointChart_SRCS})

target_link_libraries(PointChart testtools KChart Qt5::Widgets)
