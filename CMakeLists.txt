cmake_minimum_required(VERSION 2.8.12)

project( kde-kdchart )

find_package(ECM 1.4.0 REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
# include(KDEFrameworkCompilerSettings) fails for some reason with qmap const/non-const overloads
include(KDECompilerSettings)
include(KDECMakeSettings)

include(FeatureSummary)
include(GenerateExportHeader)

include(ECMGenerateHeaders)

set(REQUIRED_QT_VERSION "5.2.0")

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE
    COMPONENTS
    Core
    Gui
    PrintSupport
    Svg
    Widgets
)
find_package(Qt5Test QUIET)
if (NOT Qt5Test_FOUND)
  message(STATUS "Qt5Test not found, unit tests will not be built.")
endif()

# We want users of kdchart to be able to use the lib without interference with Qt-specific keywords, e.g. "signals" that collides with Boost's Signals
add_definitions(
    -DQT_NO_KEYWORDS
    -Demit=
)
add_definitions(
    -DQT_USE_QSTRINGBUILDER
    -DQT_NO_CAST_TO_ASCII
    -DQT_NO_CAST_FROM_ASCII
    -DQT_NO_CAST_FROM_BYTEARRAY
)

set( KDEKDCHARTLIBS_MAJOR_VERSION 2 )
set( KDEKDCHARTLIBS_MINOR_VERSION 6 )
set( KDEKDCHARTLIBS_PATCHLEVEL_VERSION 0 )
set( KDEKDCHARTLIBS_VERSION "${KDEKDCHARTLIBS_MAJOR_VERSION}.${KDEKDCHARTLIBS_MINOR_VERSION}.${KDEKDCHARTLIBS_PATCHLEVEL_VERSION}" )
set( KDEKDCHARTLIBS_ABI_VERSION 1 )

set( KDEKDCHARTLIBS_LIB_SOVERSION ${KDEKDCHARTLIBS_ABI_VERSION} )
set( KDEKDCHARTLIBS_LIB_VERSION ${KDEKDCHARTLIBS_VERSION} )

add_subdirectory( src )

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
