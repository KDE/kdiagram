set( testtools_LIB_SRCS
    TableModel.cpp
    TableModel.h
)

add_library(testtools SHARED ${testtools_LIB_SRCS})

generate_export_header( testtools )

target_link_libraries(testtools LINK_PRIVATE
    Qt::Core
)
