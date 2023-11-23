set(TestKChartBarDiagrams_SRCS
    main.cpp
)

qt_add_resources(TestKChartBarDiagrams_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestKChartBarDiagrams_SRCS}
    TEST_NAME TestKChartBarDiagrams
    LINK_LIBRARIES testtools KChartQt6 Qt::Widgets Qt::Test
)
