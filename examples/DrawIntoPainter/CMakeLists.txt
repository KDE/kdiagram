set(DrawIntoPainter_SRCS
    framewidget.cpp
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(DrawIntoPainter_SRCS
    mainwindow.ui
)

qt5_add_resources(DrawIntoPainter_SRCS
    DrawIntoPainter.qrc
)

add_executable(DrawIntoPainter  ${DrawIntoPainter_SRCS})

target_link_libraries(DrawIntoPainter testtools KChart Qt5::Widgets Qt5::PrintSupport)
