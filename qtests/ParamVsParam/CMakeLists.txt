set(TestParamVsParam_SRCS
    ModelParamVsParam.cpp
    ModelParamVsParamPlot.cpp
    mainwindow.cpp
    main.cpp
)

ecm_add_test(
    ${TestParamVsParam_SRCS}
    TEST_NAME TestParamVsParam
    LINK_LIBRARIES testtools KChartQt6 Qt::Widgets Qt::Test
)
