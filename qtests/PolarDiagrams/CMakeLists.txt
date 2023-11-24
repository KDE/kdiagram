set(TestPolarDiagrams_SRCS
    main.cpp
)

qt_add_resources(TestPolarDiagrams_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestPolarDiagrams_SRCS}
    TEST_NAME TestPolarDiagrams
    LINK_LIBRARIES testtools KChart6 Qt::Widgets Qt::Test
)
