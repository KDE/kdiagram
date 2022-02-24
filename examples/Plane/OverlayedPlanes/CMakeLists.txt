set(OverlayedPlanes_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_wrap_ui(OverlayedPlanes_SRCS
    mainwindow.ui
)

qt_add_resources(OverlayedPlanes_SRCS
    OverlayedPlanes.qrc
)

add_executable(OverlayedPlanes  ${OverlayedPlanes_SRCS})

target_link_libraries(OverlayedPlanes testtools KChart Qt::Widgets)
