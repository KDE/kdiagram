set(TestKChartAxisOwnership_SRCS
    main.cpp
)

qt_add_resources(TestKChartAxisOwnership_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestKChartAxisOwnership_SRCS}
    TEST_NAME TestKChartAxisOwnership
    LINK_LIBRARIES testtools KChartQt6 Qt::Widgets Qt::Test
)
