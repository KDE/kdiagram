set(TableView_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_add_resources(TableView_SRCS
    ModelView.qrc
)

add_executable(TableView  ${TableView_SRCS})

target_link_libraries(TableView testtools KChart Qt5::Widgets)
