set(TestCartesianPlanes_SRCS
    main.cpp
)

qt_add_resources(TestCartesianPlanes_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestCartesianPlanes_SRCS}
    TEST_NAME TestCartesianPlanes
    LINK_LIBRARIES testtools KChart6 Qt::Widgets Qt::Test
)
