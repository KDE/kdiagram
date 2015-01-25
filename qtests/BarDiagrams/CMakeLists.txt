set(TestKDChartBarDiagrams_SRCS
    main.cpp
)

qt5_add_resources(TestKDChartBarDiagrams_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestKDChartBarDiagrams_SRCS}
    TEST_NAME TestKDChartBarDiagrams
    LINK_LIBRARIES testtools KDEKDChart Qt5::Widgets Qt5::Test
)
