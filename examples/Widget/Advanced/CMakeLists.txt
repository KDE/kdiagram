set(WidgetAdvanced_SRCS
    mainwindow.cpp
    main.cpp
)

qt_wrap_ui(WidgetAdvanced_SRCS
    mainwindow.ui
)

add_executable(WidgetAdvanced  ${WidgetAdvanced_SRCS})

target_link_libraries(WidgetAdvanced KChart Qt5::Widgets)
