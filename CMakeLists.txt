cmake_minimum_required(VERSION 2.8.12)

project( kde-kdchart )

find_package(ECM 1.4.0 REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings)
include(KDECMakeSettings)

include(FeatureSummary)
include(GenerateExportHeader)

include(ECMGenerateHeaders)
include(ECMSetupVersion)
include(ECMPackageConfigHelpers)
include(ECMGeneratePriFile)

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

set( KDEKDCHARTLIBS_VERSION "2.6.0" )

add_subdirectory( src )

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
