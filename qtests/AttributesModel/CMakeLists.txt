set(TestKChartAttributesModel_SRCS
    main.cpp
)

qt5_add_resources(TestKChartAttributesModel_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestKChartAttributesModel_SRCS}
    TEST_NAME TestKChartAttributesModel
    LINK_LIBRARIES testtools KChart Qt5::Widgets Qt5::Test
)
