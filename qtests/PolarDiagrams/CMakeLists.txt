set(TestPolarDiagrams_SRCS
    main.cpp
)

qt5_add_resources(TestPolarDiagrams_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestPolarDiagrams_SRCS}
    TEST_NAME TestPolarDiagrams
    LINK_LIBRARIES testtools KChart Qt5::Widgets Qt5::Test
)
