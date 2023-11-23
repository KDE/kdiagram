
# qt_add_resources(TestKChartAttributesModel_SRCS
#     Data.qrc
# )

ecm_add_test(TestKGanttConstraint.cpp
    TEST_NAME KGanttConstraint
    LINK_LIBRARIES KGanttQt6 Qt::Test
)

ecm_add_test(TestKGanttConstraintModel.cpp
    TEST_NAME KGanttConstraintModel
    LINK_LIBRARIES KGanttQt6 Qt::Test
)

ecm_add_test(TestMultiItems.cpp
    TEST_NAME KGanttMultiItems
    LINK_LIBRARIES KGanttQt6 Qt::Test
)

ecm_add_test(TestKGanttView.cpp
    TEST_NAME KGanttView
    LINK_LIBRARIES PUBLIC KGanttQt6 Qt::Test
)
