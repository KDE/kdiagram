set(TernaryChartsAdvanced_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(TernaryChartsAdvanced_SRCS
    mainwindow.ui
)

add_executable(TernaryChartsAdvanced  ${TernaryChartsAdvanced_SRCS})

target_link_libraries(TernaryChartsAdvanced KChart Qt5::Widgets)
