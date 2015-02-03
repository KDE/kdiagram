set(PlotterTimeline_SRCS
    timeaxis.cpp
    timechartmodel.cpp
    main.cpp
)

add_executable(PlotterTimeline  ${PlotterTimeline_SRCS})

target_link_libraries(PlotterTimeline KChart Qt5::Widgets)
