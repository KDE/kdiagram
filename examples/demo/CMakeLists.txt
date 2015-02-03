set(demo_SRCS
    datasetsettings.cpp
    gradientdialog.cpp
    colorslider.cpp
    diagramsettings.cpp
    datavaluesettings.cpp
    diagramtypedialog.cpp
    axissettings.cpp
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(demo_SRCS
    datasetsettings.ui
    gradientdialog.ui
    diagramsettings.ui
    datavaluesettings.ui
    diagramtypedialog.ui
    axissettings.ui
)

qt5_add_resources(demo_SRCS
    demo.qrc
)

add_executable(demo  ${demo_SRCS})

target_link_libraries(demo testtools KChart Qt5::Widgets)
