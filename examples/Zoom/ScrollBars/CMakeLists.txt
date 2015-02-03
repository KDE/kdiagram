set(ZoomScrollBars_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(ZoomScrollBars_SRCS
    mainwindow.ui
)

qt5_add_resources(ZoomScrollBars_SRCS
    ZoomScrollBars.qrc
)

add_executable(ZoomScrollBars  ${ZoomScrollBars_SRCS})

target_link_libraries(ZoomScrollBars testtools KChart Qt5::Widgets)
