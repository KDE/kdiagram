set(DataValueTexts_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(DataValueTexts_SRCS
    mainwindow.ui
)

qt5_add_resources(DataValueTexts_SRCS
    DataValueTexts.qrc
)

add_executable(DataValueTexts  ${DataValueTexts_SRCS})

target_link_libraries(DataValueTexts testtools KChart Qt5::Widgets)
