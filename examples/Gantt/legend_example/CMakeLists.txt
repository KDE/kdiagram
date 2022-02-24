set(legend_example_SRCS
    entrydialog.cpp
    entrydelegate.cpp
    mainwindow.cpp
    entrydialog.h
    entrydelegate.h
    mainwindow.h
    main.cpp
)

qt_wrap_ui(legend_example_SRCS
    entrydialog.ui
    mainwindow.ui
)

add_executable(legend_example  ${legend_example_SRCS})

target_link_libraries(legend_example KGantt Qt::Widgets Qt::PrintSupport)
