set(DrawIntoPainter_SRCS
    framewidget.cpp
    mainwindow.cpp
    framewidget.h
    mainwindow.h
    main.cpp
)

qt_wrap_ui(DrawIntoPainter_SRCS
    mainwindow.ui
)

qt_add_resources(DrawIntoPainter_SRCS
    DrawIntoPainter.qrc
)

add_executable(DrawIntoPainter  ${DrawIntoPainter_SRCS})

target_link_libraries(DrawIntoPainter testtools KChart6 Qt::Widgets Qt::PrintSupport)
