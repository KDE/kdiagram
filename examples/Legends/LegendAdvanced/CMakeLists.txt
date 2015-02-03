set(LegendAdvanced_SRCS
    derivedaddlegenddialog.cpp
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(LegendAdvanced_SRCS
    addlegenddialog.ui
    mainwindow.ui
)

qt5_add_resources(LegendAdvanced_SRCS
    Legends.qrc
)

add_executable(LegendAdvanced  ${LegendAdvanced_SRCS})

target_link_libraries(LegendAdvanced testtools KChart Qt5::Widgets)
