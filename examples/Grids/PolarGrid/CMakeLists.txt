set(PolarGrid_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_wrap_ui(PolarGrid_SRCS
    mainwindow.ui
)

add_executable(PolarGrid  ${PolarGrid_SRCS})

target_link_libraries(PolarGrid KChart6 Qt::Widgets)
