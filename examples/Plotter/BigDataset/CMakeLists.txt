set(BigDataset_SRCS
    MainWidget.cpp
    Model.cpp
    main.cpp
)

qt5_wrap_ui(BigDataset_SRCS
    Controls.ui
)

add_executable(BigDataset  ${BigDataset_SRCS})

target_link_libraries(BigDataset KDEKDChart Qt5::Widgets)
