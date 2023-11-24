set(GanttPalette_SRCS
    ../common/projectmodel.cpp
    mainwindow.cpp
    ../common/projectmodel.h
    mainwindow.h
    main.cpp
)

add_executable(GanttPalette  ${GanttPalette_SRCS})

target_link_libraries(GanttPalette KGantt6 Qt::Widgets Qt::PrintSupport)
