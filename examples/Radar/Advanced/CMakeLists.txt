set(RadarAdvanced_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(RadarAdvanced_SRCS
    mainwindow.ui
)

add_executable(RadarAdvanced  ${RadarAdvanced_SRCS})

target_link_libraries(RadarAdvanced KChart Qt5::Widgets)
