set(TestPolarPlanes_SRCS
    main.cpp
)

qt5_add_resources(TestPolarPlanes_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestPolarPlanes_SRCS}
    TEST_NAME TestPolarPlanes
    LINK_LIBRARIES testtools KChart Qt5::Widgets Qt5::Test
)
