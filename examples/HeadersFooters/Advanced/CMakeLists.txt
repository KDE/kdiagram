set(HeadersFootersAdvanced_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_wrap_ui(HeadersFootersAdvanced_SRCS
    addheaderdialog.ui
    mainwindow.ui
)

qt_add_resources(HeadersFootersAdvanced_SRCS
    HeadersFooters.qrc
)

add_executable(HeadersFootersAdvanced  ${HeadersFootersAdvanced_SRCS})

target_link_libraries(HeadersFootersAdvanced testtools KChart6 Qt::Widgets Qt::PrintSupport)
