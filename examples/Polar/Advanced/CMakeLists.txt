set(PolarAdvanced_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_wrap_ui(PolarAdvanced_SRCS
    mainwindow.ui
)

add_executable(PolarAdvanced  ${PolarAdvanced_SRCS})

target_link_libraries(PolarAdvanced KChart6 Qt::Widgets)
