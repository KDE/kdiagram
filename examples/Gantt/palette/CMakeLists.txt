set(GanttPalette_SRCS
    ../common/projectmodel.cpp
    mainwindow.cpp
    main.cpp
)

add_executable(GanttPalette  ${GanttPalette_SRCS})

target_link_libraries(GanttPalette KGantt Qt5::Widgets Qt5::PrintSupport)
