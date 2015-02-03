set(TestLineDiagrams_SRCS
    main.cpp
)

qt5_add_resources(TestLineDiagrams_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestLineDiagrams_SRCS}
    TEST_NAME TestLineDiagrams
    LINK_LIBRARIES testtools KChart Qt5::Widgets Qt5::Test
)
