set(EmptyValues_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_add_resources(EmptyValues_SRCS
    BarChart.qrc
)

add_executable(EmptyValues  ${EmptyValues_SRCS})

target_link_libraries(EmptyValues testtools KChart Qt::Widgets)
