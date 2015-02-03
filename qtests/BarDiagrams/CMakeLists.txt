set(TestKChartBarDiagrams_SRCS
    main.cpp
)

qt5_add_resources(TestKChartBarDiagrams_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestKChartBarDiagrams_SRCS}
    TEST_NAME TestKChartBarDiagrams
    LINK_LIBRARIES testtools KChart Qt5::Widgets Qt5::Test
)
