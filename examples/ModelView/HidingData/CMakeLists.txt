set(HidingData_SRCS
    mainwindow.cpp
    main.cpp
)

qt_wrap_ui(HidingData_SRCS
    mainwindow.ui
)

qt_add_resources(HidingData_SRCS
    ModelView.qrc
)

add_executable(HidingData  ${HidingData_SRCS})

target_link_libraries(HidingData testtools KChart Qt::Widgets)
