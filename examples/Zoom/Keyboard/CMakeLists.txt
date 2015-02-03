set(ZoomKeyboard_SRCS
    zoomwidget.cpp
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(ZoomKeyboard_SRCS
    mainwindow.ui
)

add_executable(ZoomKeyboard  ${ZoomKeyboard_SRCS})

target_link_libraries(ZoomKeyboard KChart Qt5::Widgets)
