set(DrawIntoPainter_SRCS
    framewidget.cpp
    mainwindow.cpp
    main.cpp
)

qt_wrap_ui(DrawIntoPainter_SRCS
    mainwindow.ui
)

qt_add_resources(DrawIntoPainter_SRCS
    DrawIntoPainter.qrc
)

add_executable(DrawIntoPainter  ${DrawIntoPainter_SRCS})

target_link_libraries(DrawIntoPainter testtools KChart Qt5::Widgets Qt5::PrintSupport)
