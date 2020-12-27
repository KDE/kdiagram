set(GanttPrinting_SRCS
    ../common/projectmodel.cpp
    mainwindow.cpp
    main.cpp
)

add_executable(GanttPrinting  ${GanttPrinting_SRCS})

target_link_libraries(GanttPrinting KGantt Qt5::Widgets Qt5::PrintSupport)
