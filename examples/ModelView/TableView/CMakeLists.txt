set(TableView_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_add_resources(TableView_SRCS
    ModelView.qrc
)

add_executable(TableView  ${TableView_SRCS})

target_link_libraries(TableView testtools KChart Qt::Widgets)
