set(TestKDChartAxisOwnership_SRCS
    main.cpp
)

qt5_add_resources(TestKDChartAxisOwnership_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestKDChartAxisOwnership_SRCS}
    TEST_NAME TestKDChartAxisOwnership
    LINK_LIBRARIES testtools KDEKDChart Qt5::Widgets Qt5::Test
)
