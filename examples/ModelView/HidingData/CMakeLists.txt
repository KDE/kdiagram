set(HidingData_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(HidingData_SRCS
    mainwindow.ui
)

qt5_add_resources(HidingData_SRCS
    ModelView.qrc
)

add_executable(HidingData  ${HidingData_SRCS})

target_link_libraries(HidingData testtools KChart Qt5::Widgets)
