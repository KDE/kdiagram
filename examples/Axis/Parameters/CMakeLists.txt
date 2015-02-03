set(AxisParameters_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(AxisParameters_SRCS
    mainwindow.ui
)

qt5_add_resources(AxisParameters_SRCS
    Axes.qrc
)

add_executable(AxisParameters  ${AxisParameters_SRCS})

target_link_libraries(AxisParameters testtools KChart Qt5::Widgets)
