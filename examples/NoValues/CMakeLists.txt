set(NoValues_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

add_executable(NoValues  ${NoValues_SRCS})

target_link_libraries(NoValues KChart Qt::Widgets)
