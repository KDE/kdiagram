set(TestDrawIntoPainter_SRCS
    framewidget.cpp
    mainwindow.cpp
    main.cpp
)

qt_wrap_ui(TestDrawIntoPainter_SRCS
    mainwindow.ui
)

qt_add_resources(TestDrawIntoPainter_SRCS
    DrawIntoPainter.qrc
)

ecm_add_test(
    ${TestDrawIntoPainter_SRCS}
    TEST_NAME TestDrawIntoPainter
    LINK_LIBRARIES testtools KChart Qt::Widgets Qt::Test
)

set_property(TEST TestDrawIntoPainter PROPERTY TIMEOUT 600)
