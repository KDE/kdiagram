set(PolarAdvanced_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(PolarAdvanced_SRCS
    mainwindow.ui
)

add_executable(PolarAdvanced  ${PolarAdvanced_SRCS})

target_link_libraries(PolarAdvanced KChart Qt5::Widgets)
