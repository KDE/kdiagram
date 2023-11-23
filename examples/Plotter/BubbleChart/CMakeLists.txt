set(BubbleChart_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_wrap_ui(BubbleChart_SRCS
    mainwindow.ui
)

add_executable(BubbleChart  ${BubbleChart_SRCS})

target_link_libraries(BubbleChart KChartQt6 Qt::Widgets)
