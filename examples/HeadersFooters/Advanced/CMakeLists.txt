set(HeadersFootersAdvanced_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(HeadersFootersAdvanced_SRCS
    addheaderdialog.ui
    mainwindow.ui
)

qt5_add_resources(HeadersFootersAdvanced_SRCS
    HeadersFooters.qrc
)

add_executable(HeadersFootersAdvanced  ${HeadersFootersAdvanced_SRCS})

target_link_libraries(HeadersFootersAdvanced testtools KChart Qt5::Widgets Qt5::PrintSupport)
