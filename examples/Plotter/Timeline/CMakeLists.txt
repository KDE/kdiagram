set(PlotterTimeline_SRCS
    timeaxis.cpp
    timechartmodel.cpp
    timeaxis.h
    timechartmodel.h
    main.cpp
)

add_executable(PlotterTimeline  ${PlotterTimeline_SRCS})

target_link_libraries(PlotterTimeline KChart6 Qt::Widgets)
