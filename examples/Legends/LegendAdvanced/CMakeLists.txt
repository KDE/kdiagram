set(LegendAdvanced_SRCS
    derivedaddlegenddialog.cpp
    mainwindow.cpp
    derivedaddlegenddialog.h
    mainwindow.h
    main.cpp
)

qt_wrap_ui(LegendAdvanced_SRCS
    addlegenddialog.ui
    mainwindow.ui
)

qt_add_resources(LegendAdvanced_SRCS
    Legends.qrc
)

add_executable(LegendAdvanced  ${LegendAdvanced_SRCS})

target_link_libraries(LegendAdvanced testtools KChart Qt::Widgets)
