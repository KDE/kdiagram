set(LinesAdvanced_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(LinesAdvanced_SRCS
    mainwindow.ui
)

qt5_add_resources(LinesAdvanced_SRCS
    LineChart.qrc
)

add_executable(LinesAdvanced  ${LinesAdvanced_SRCS})

target_link_libraries(LinesAdvanced testtools KChart Qt5::Widgets)
