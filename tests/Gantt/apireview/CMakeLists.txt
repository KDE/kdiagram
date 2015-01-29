set(TestApiReview_SRCS
    entrydialog.cpp
    entrydelegate.cpp
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(TestApiReview_SRCS
    entrydialog.ui
    mainwindow.ui
)

add_executable(TestApiReview  ${TestApiReview_SRCS})

target_link_libraries(TestApiReview KGantt Qt5::Widgets Qt5::PrintSupport)
