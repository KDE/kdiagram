set(EmptyValues_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_add_resources(EmptyValues_SRCS
    BarChart.qrc
)

add_executable(EmptyValues  ${EmptyValues_SRCS})

target_link_libraries(EmptyValues testtools KChart Qt5::Widgets)
