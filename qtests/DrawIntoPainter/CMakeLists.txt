set(TestDrawIntoPainter_SRCS
    framewidget.cpp
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(TestDrawIntoPainter_SRCS
    mainwindow.ui
)

qt5_add_resources(TestDrawIntoPainter_SRCS
    DrawIntoPainter.qrc
)

ecm_add_test(
    ${TestDrawIntoPainter_SRCS}
    TEST_NAME TestDrawIntoPainter
    LINK_LIBRARIES testtools KChart Qt5::Widgets Qt5::Test
)

set_property(TEST TestDrawIntoPainter PROPERTY TIMEOUT 600)
