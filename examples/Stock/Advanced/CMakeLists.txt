set(StockDiagram_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(StockDiagram_SRCS
    mainwindow.ui
)

qt5_add_resources(StockDiagram_SRCS
    Resources.qrc
)

add_executable(StockDiagram  ${StockDiagram_SRCS})

target_link_libraries(StockDiagram testtools KChart Qt5::Widgets)
