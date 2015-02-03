set(BarsAdvanced_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(BarsAdvanced_SRCS
    mainwindow.ui
)

qt5_add_resources(BarsAdvanced_SRCS
    BarChart.qrc
)

add_executable(BarsAdvanced  ${BarsAdvanced_SRCS})

target_link_libraries(BarsAdvanced testtools KChart Qt5::Widgets)
