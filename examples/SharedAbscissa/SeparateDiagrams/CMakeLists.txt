set(SeparateDiagrams_SRCS
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

qt_wrap_ui(SeparateDiagrams_SRCS
    mainwindow.ui
)

qt_add_resources(SeparateDiagrams_SRCS
    SharedAbscissa.qrc
)

add_executable(SeparateDiagrams  ${SeparateDiagrams_SRCS})

target_link_libraries(SeparateDiagrams testtools KChart6 Qt::Widgets)
