set(BarsAdvanced_SRCS
    mainwindow.h
    mainwindow.cpp
    main.cpp
)

qt_wrap_ui(BarsAdvanced_SRCS
    mainwindow.ui
)

qt_add_resources(BarsAdvanced_SRCS
    BarChart.qrc
)

add_executable(BarsAdvanced  ${BarsAdvanced_SRCS})

target_link_libraries(BarsAdvanced testtools KChart Qt::Widgets)
