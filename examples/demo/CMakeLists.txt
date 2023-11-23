set(demo_SRCS
    datasetsettings.cpp
    gradientdialog.cpp
    colorslider.cpp
    diagramsettings.cpp
    datavaluesettings.cpp
    diagramtypedialog.cpp
    axissettings.cpp
    mainwindow.cpp
    datasetsettings.h
    gradientdialog.h
    colorslider.h
    diagramsettings.h
    datavaluesettings.h
    diagramtypedialog.h
    axissettings.h
    mainwindow.h
    main.cpp
)

qt_wrap_ui(demo_SRCS
    datasetsettings.ui
    gradientdialog.ui
    diagramsettings.ui
    datavaluesettings.ui
    diagramtypedialog.ui
    axissettings.ui
)

qt_add_resources(demo_SRCS
    demo.qrc
)

add_executable(demo  ${demo_SRCS})

target_link_libraries(demo testtools KChartQt6 Qt::Widgets)
