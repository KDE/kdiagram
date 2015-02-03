set(TestCartesianPlanes_SRCS
    main.cpp
)

qt5_add_resources(TestCartesianPlanes_SRCS
    Data.qrc
)

ecm_add_test(
    ${TestCartesianPlanes_SRCS}
    TEST_NAME TestCartesianPlanes
    LINK_LIBRARIES testtools KChart Qt5::Widgets Qt5::Test
)
