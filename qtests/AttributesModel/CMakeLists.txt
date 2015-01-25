set(TestKDChartAttributesModel_SRCS
    main.cpp
)

qt5_add_resources(TestKDChartAttributesModel_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestKDChartAttributesModel_SRCS}
    TEST_NAME TestKDChartAttributesModel
    LINK_LIBRARIES testtools KDEKDChart Qt5::Widgets Qt5::Test
)
