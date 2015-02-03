set(BubbleChart_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(BubbleChart_SRCS
    mainwindow.ui
)

add_executable(BubbleChart  ${BubbleChart_SRCS})

target_link_libraries(BubbleChart KChart Qt5::Widgets)
