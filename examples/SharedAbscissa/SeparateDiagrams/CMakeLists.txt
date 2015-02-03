set(SeparateDiagrams_SRCS
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(SeparateDiagrams_SRCS
    mainwindow.ui
)

qt5_add_resources(SeparateDiagrams_SRCS
    SharedAbscissa.qrc
)

add_executable(SeparateDiagrams  ${SeparateDiagrams_SRCS})

target_link_libraries(SeparateDiagrams testtools KChart Qt5::Widgets)
