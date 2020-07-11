cmake_minimum_required(VERSION 2.8.12)

project( kdiagram )

set(KF5_MIN_VERSION "5.60.0")
find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)

include(FeatureSummary)
include(GenerateExportHeader)

include(ECMGenerateHeaders)
include(ECMSetupVersion)
include(ECMPackageConfigHelpers)
include(ECMGeneratePriFile)
include(ECMPoQmTools)
include(ECMAddTests)
set(QT_REQUIRED_VERSION "5.12.0")

include(CMakeDependentOption)

set(HAS_ECMAddQch TRUE)
include(ECMAddQch)

cmake_dependent_option(BUILD_QCH
    "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF
    "HAS_ECMAddQch" OFF
)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")

find_package(Qt5 ${QT_REQUIRED_VERSION} REQUIRED NO_MODULE
    COMPONENTS
    PrintSupport
    Svg
    Widgets
)
if(BUILD_TESTING)
    find_package(Qt5Test QUIET)
    if (NOT Qt5Test_FOUND)
        message(STATUS "Qt5Test not found, unit tests will not be built.")
    endif()
endif()

find_package(Qt5Sql QUIET)
if (NOT Qt5Sql_FOUND)
    message(STATUS "Qt5Sql not found, examples with SQL will not be built.")
endif()

# We want users of kdiagram libs to be able to use the lib without interference with Qt-specific keywords, e.g. "signals" that collides with Boost's Signals
add_definitions(
    -DQT_NO_KEYWORDS
    -Demit=
)
add_definitions(
    -DQT_NO_STL
    -DQT_FATAL_ASSERT
    -DUSE_EXCEPTIONS
)

# TODO: port from .pro
#  NOMINMAX avoids conflicting definitions of min and max
#  _USE_MATH_DEFINES makes M_PI defined
# win32 {
# !win32-g++ {
#     DEFINES += NOMINMAX _USE_MATH_DEFINES
#     QMAKE_CXXFLAGS += /GR /EHsc /wd4251
# }
# }

# TODO: port g++.pri to cmake and check what is still needed


if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/po")
    ecm_install_po_files_as_qm(po)
endif()

add_subdirectory( src )

if(BUILD_TESTING)
    add_subdirectory( examples )
    add_subdirectory( tests )

    if(Qt5Test_FOUND)
        add_subdirectory( qtests )
    endif()
endif()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
