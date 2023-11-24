set(TestApiReview_SRCS
    entrydialog.cpp
    entrydelegate.cpp
    mainwindow.cpp
    entrydialog.h
    entrydelegate.h
    mainwindow.h
    main.cpp
)

qt_wrap_ui(TestApiReview_SRCS
    entrydialog.ui
    mainwindow.ui
)

add_executable(TestApiReview  ${TestApiReview_SRCS})

target_link_libraries(TestApiReview KGantt6 Qt::Widgets Qt::PrintSupport)
