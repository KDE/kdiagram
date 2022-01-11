set(AxisParameters_SRCS
    mainwindow.cpp
    main.cpp
)

qt_wrap_ui(AxisParameters_SRCS
    mainwindow.ui
)

qt_add_resources(AxisParameters_SRCS
    Axes.qrc
)

add_executable(AxisParameters  ${AxisParameters_SRCS})

target_link_libraries(AxisParameters testtools KChart Qt5::Widgets)
