set(TestMeasure_SRCS
    main.cpp
)

qt_add_resources(TestMeasure_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestMeasure_SRCS}
    TEST_NAME TestMeasure
    LINK_LIBRARIES testtools KChart6 Qt::Widgets Qt::Test
)
