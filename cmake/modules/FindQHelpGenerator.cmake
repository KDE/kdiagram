# Finds the Qt5 QHelpGenerator
#
#  QHelpGenerator_FOUND     - True if QHelpGenerator found.
#  QHelpGenerator_EXECUTABLE - Path to executable

# try 
find_package(Qt5Core QUIET)
if (TARGET Qt5::qhelpgenerator)
    get_target_property(QHelpGenerator_EXECUTABLE Qt5::qhelpgenerator LOCATION)
else()
    # assume same folder as qmake executable
    if (TARGET Qt5::qmake)
        get_target_property(_qmake_EXECUTABLE Qt5::qmake LOCATION)
        get_filename_component(_path ${_qmake_EXECUTABLE} DIRECTORY)
    else()
        set(_path)
    endif()
    # TODO: prevent that the Qt4 version is picked up
    find_program(QHelpGenerator_EXECUTABLE
        NAMES
            qhelpgenerator-qt5
            qhelpgenerator
        PATH
            ${_path}
    )
endif()
mark_as_advanced(QHelpGenerator_EXECUTABLE)

if(QHelpGenerator_EXECUTABLE)
    set(QHelpGenerator_FOUND TRUE)
else()
    set(QHelpGenerator_FOUND FALSE)
endif()

if(QHelpGenerator_FOUND)
  if(NOT QHelpGenerator_FIND_QUIETLY )
    message( STATUS "Found QHelpGenerator executable: ${QHelpGenerator_EXECUTABLE}")
  endif()
else()
  if(QHelpGenerator_FIND_REQUIRED)
    message( FATAL_ERROR "Could not find QHelpGenerator executable" )
  else()
    message( STATUS "Optional QHelpGenerator executable was not found" )
  endif()
endif()

