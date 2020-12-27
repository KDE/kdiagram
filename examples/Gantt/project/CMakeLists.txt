set(project_SRCS
    ../common/projectmodel.cpp
    mainwindow.cpp
    main.cpp
)

add_executable(project  ${project_SRCS})

target_link_libraries(project KGantt Qt5::Widgets Qt5::PrintSupport)
