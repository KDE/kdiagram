set(StockDiagram_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_wrap_ui(StockDiagram_SRCS
    mainwindow.ui
)

qt_add_resources(StockDiagram_SRCS
    Resources.qrc
)

add_executable(StockDiagram  ${StockDiagram_SRCS})

target_link_libraries(StockDiagram testtools KChartQt6 Qt::Widgets)
