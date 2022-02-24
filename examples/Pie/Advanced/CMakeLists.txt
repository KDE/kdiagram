set(PieAdvanced_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_wrap_ui(PieAdvanced_SRCS
    mainwindow.ui
)

qt_add_resources(PieAdvanced_SRCS
    Pie.qrc
)

add_executable(PieAdvanced  ${PieAdvanced_SRCS})

target_link_libraries(PieAdvanced testtools KChart Qt::Widgets)
