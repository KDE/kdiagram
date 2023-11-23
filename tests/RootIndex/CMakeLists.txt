set(RootIndex_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_wrap_ui(RootIndex_SRCS
    mainwindow.ui
)

add_executable(RootIndex  ${RootIndex_SRCS})

target_link_libraries(RootIndex KChartQt6 Qt::Widgets)
