set(TestLineDiagrams_SRCS
    main.cpp
)

qt_add_resources(TestLineDiagrams_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestLineDiagrams_SRCS}
    TEST_NAME TestLineDiagrams
    LINK_LIBRARIES testtools KChart6 Qt::Widgets Qt::Test
)
