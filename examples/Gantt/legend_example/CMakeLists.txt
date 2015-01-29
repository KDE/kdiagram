set(legend_example_SRCS
    entrydialog.cpp
    entrydelegate.cpp
    mainwindow.cpp
    main.cpp
)

qt5_wrap_ui(legend_example_SRCS
    entrydialog.ui
    mainwindow.ui
)

add_executable(legend_example  ${legend_example_SRCS})

target_link_libraries(legend_example KGantt Qt5::Widgets Qt5::PrintSupport)
