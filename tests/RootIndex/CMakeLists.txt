set(RootIndex_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(RootIndex_SRCS
    mainwindow.ui
)

add_executable(RootIndex  ${RootIndex_SRCS})

target_link_libraries(RootIndex KDEKDChart Qt5::Widgets)
