set(GanttPrinting_SRCS
    ../common/projectmodel.cpp
    mainwindow.cpp
    main.cpp
)

add_executable(GanttPrinting  ${GanttPrinting_SRCS})

target_link_libraries(GanttPrinting KGantt Qt::Widgets Qt::PrintSupport)
