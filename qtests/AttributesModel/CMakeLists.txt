set(TestKChartAttributesModel_SRCS
    main.cpp
)

qt_add_resources(TestKChartAttributesModel_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestKChartAttributesModel_SRCS}
    TEST_NAME TestKChartAttributesModel
    LINK_LIBRARIES testtools KChart Qt::Widgets Qt::Test
)
