set(TestPieDiagrams_SRCS
    main.cpp
)

qt_add_resources(TestPieDiagrams_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestPieDiagrams_SRCS}
    TEST_NAME TestPieDiagrams
    LINK_LIBRARIES testtools KChart6 Qt::Widgets Qt::Test
)
