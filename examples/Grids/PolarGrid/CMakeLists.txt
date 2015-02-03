set(PolarGrid_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(PolarGrid_SRCS
    mainwindow.ui
)

add_executable(PolarGrid  ${PolarGrid_SRCS})

target_link_libraries(PolarGrid KChart Qt5::Widgets)
