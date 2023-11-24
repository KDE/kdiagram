set(ZoomKeyboard_SRCS
    zoomwidget.cpp
    mainwindow.cpp
    zoomwidget.h
    mainwindow.h
    main.cpp
)

qt_wrap_ui(ZoomKeyboard_SRCS
    mainwindow.ui
)

add_executable(ZoomKeyboard  ${ZoomKeyboard_SRCS})

target_link_libraries(ZoomKeyboard KChart6 Qt::Widgets)
