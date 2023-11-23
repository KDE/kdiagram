set(GanttPrinting_SRCS
    ../common/projectmodel.cpp
    mainwindow.cpp
    ../common/projectmodel.h
    mainwindow.h
    main.cpp
)

add_executable(GanttPrinting  ${GanttPrinting_SRCS})

target_link_libraries(GanttPrinting KGanttQt6 Qt::Widgets Qt::PrintSupport)
