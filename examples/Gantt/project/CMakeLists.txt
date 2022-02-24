set(project_SRCS
    ../common/projectmodel.cpp
    mainwindow.cpp
    ../common/projectmodel.h
    mainwindow.h
    main.cpp
)

add_executable(project  ${project_SRCS})

target_link_libraries(project KGantt Qt::Widgets Qt::PrintSupport)
