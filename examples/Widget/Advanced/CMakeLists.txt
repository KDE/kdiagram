set(WidgetAdvanced_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(WidgetAdvanced_SRCS
    mainwindow.ui
)

add_executable(WidgetAdvanced  ${WidgetAdvanced_SRCS})

target_link_libraries(WidgetAdvanced KDEKDChart Qt5::Widgets)
