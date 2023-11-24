set(BigDataset_SRCS
    MainWidget.cpp
    Model.cpp
    MainWidget.h
    Model.h
    main.cpp
)

qt_wrap_ui(BigDataset_SRCS
    Controls.ui
)

add_executable(BigDataset  ${BigDataset_SRCS})

target_link_libraries(BigDataset KChart6 Qt::Widgets)
