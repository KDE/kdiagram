set(NoValues_SRCS
    mainwindow.cpp
    main.cpp
)

add_executable(NoValues  ${NoValues_SRCS})

target_link_libraries(NoValues KChart Qt5::Widgets)
