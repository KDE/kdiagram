set(TestPieDiagrams_SRCS
    main.cpp
)

qt5_add_resources(TestPieDiagrams_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestPieDiagrams_SRCS}
    TEST_NAME TestPieDiagrams
    LINK_LIBRARIES testtools KChart Qt5::Widgets Qt5::Test
)
