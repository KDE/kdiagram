set(TestRingDiagrams_SRCS
    main.cpp
)

qt5_add_resources(TestRingDiagrams_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestRingDiagrams_SRCS}
    TEST_NAME TestRingDiagrams
    LINK_LIBRARIES testtools KChart Qt5::Widgets Qt5::Test
)
