set( testtools_LIB_SRCS
    TableModel.cpp
)

add_definitions(
    -DTESTTOOLS_MAKEDLL
)
add_library(testtools SHARED ${testtools_LIB_SRCS})

target_link_libraries(testtools LINK_PRIVATE
    Qt5::Core
)
