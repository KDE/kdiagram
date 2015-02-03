set(TestMeasure_SRCS
    main.cpp
)

qt5_add_resources(TestMeasure_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestMeasure_SRCS}
    TEST_NAME TestMeasure
    LINK_LIBRARIES testtools KChart Qt5::Widgets Qt5::Test
)
