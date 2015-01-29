remove_definitions(
    -DQT_NO_KEYWORDS
    -DQT_NO_SIGNALS_SLOTS_KEYWORDS
    -DQT_NO_CAST_FROM_ASCII
)

add_subdirectory( apireview )
add_subdirectory( customconstraints )
add_subdirectory( gfxview )
add_subdirectory( view )
add_subdirectory( listview )
add_subdirectory( headers )
add_subdirectory( reorder )
add_subdirectory( unittest )
