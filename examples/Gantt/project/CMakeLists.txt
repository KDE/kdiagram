set(project_SRCS
    projectmodel.cpp
    mainwindow.cpp
    main.cpp
)

add_executable(project  ${project_SRCS})

target_link_libraries(project KDEKDGantt Qt5::Widgets Qt5::PrintSupport)
