set(OverlayedPlanes_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(OverlayedPlanes_SRCS
    mainwindow.ui
)

qt5_add_resources(OverlayedPlanes_SRCS
    OverlayedPlanes.qrc
)

add_executable(OverlayedPlanes  ${OverlayedPlanes_SRCS})

target_link_libraries(OverlayedPlanes testtools KChart Qt5::Widgets)
