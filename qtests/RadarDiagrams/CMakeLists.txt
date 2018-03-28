set(TestRadarDiagrams_SRCS
    main.cpp
)

qt5_add_resources(TestRadarDiagrams_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestRadarDiagrams_SRCS}
    TEST_NAME TestRadarDiagrams
    LINK_LIBRARIES testtools KChart Qt5::Widgets Qt5::Test
)
