#.rst:
# KDiagramAddQCH
# ------------------
#
# This module provides the ``kdiagram_add_qch`` function for generating API
# documentation files in the QCH format, and the ``kdiagram_install_qch_export``
# function for generating and installing exported CMake targets for such
# generated QCH files to enable builds of other software with generation of
# QCH files to create links into the given QCH files.
#
# ::
#
#   kdiagram_add_qch(<name>
#       OUTPUT_BASENAME <basename>
#       VERSION <version>
#       QCH_INSTALL_DESTINATION <qchfile_install_path>
#       TAGFILE_INSTALL_DESTINATION <tagsfile_install_path>
#       [SOURCE_DIRS <dir> [<dir2> [...]]]
#       [SOURCES <file> [<file2> [...]]]
#       |MD_MAINPAGE <md_file>]
#       [IMAGE_DIRS <idir> [<idir2> [...]]]
#       [EXAMPLE_DIRS <edir> [<edir2> [...]]]
#       [ORG_DOMAIN <domain>]
#       [NAMESPACE <namespace>]
#       [LINK_QCHS <qch> [<qch2> [...]]]
#       [LINK_QCHS_VERSIONED <qchv> [<qchv2> [...]]]
#       [BLANK_MACROS <macro> [<macro2> [...]]]
#       [CONFIG_TEMPLATE <configtemplate_file>]
#       [VERBOSE]
#   )
#
# This macro adds a target called <name> for the creation of an API
# documentation manual named ``<basename>.qch``in the QCH format from the
# given sources.
# It currently uses doxygen, future versions might optionally also allow other
# tools.
# Next to the QCH file the target will generate a corresponding doxygen tag
# file name ``<basename>.tags``, which enables creating links from other
# documentation into the generated QCH file.
#
# If the required tools are not found, the macro will skip creation of the
# target and only emit a warning, so the use of the macro can be introduced
# without requiring anyone to also have the needed tools present at that time.
# This behaviour might change in future versions to result in a fail instead.
# It is recommended to make the use of this macro optional, by depending
# the call to ``kdiagram_add_qch()`` on a CMake option being set, with a name like
# ``BUILD_QCH`` and being TRUE by default. This will allow the developers to
# saves resources on normal source development build cycles by setting this
# option to FALSE.
#
# The macro will set the target properties DOXYGEN_TAGFILE, QHP_NAMESPACE,
# QHP_NAMESPACE_VERSIONED and QHP_VIRTUALFOLDER to the respective values, to
# allow other code access to them, e.g. the macro kdiagram_install_qch_export().
# To enable the use of the target <name> as item for LINK_QCHS or
# LINK_QCHS_VERSIONED in further ``kdiagram_add_qch()`` calls in the current build,
# additionally a target property DOXYGEN_TAGFILE_BUILD is set, with the path
# of the created doxygen tag file in the build dir.
# If existing, ``kdiagram_add_qch()`` will use this property instead of
# DOXYGEN_TAGFILE for access to the tags file.
#
# OUTPUT_BASENAME specifies the base name for the generated documentation and
# the files.
#
# VERSION specifies the version of the library for which the documentation is
# created.
#
# SOURCE_DIRS specifies the dirs (incl. subdirs) with the source files for
# which the API documentation should be generated.  Dirs can be relative to
# the current source dir. Dependencies to the files in the dirs are not
# tracked currently, other than with the SOURCES argument. So do not use for
# sources generated during the build.
# Needs to be used when SOURCES or CONFIG_TEMPLATE are not used.
#
# SOURCES specifies the source files for which the API documentation should be
# generated.
# Needs to be used when SOURCE_DIRS or CONFIG_TEMPLATE are not used.
#
# MD_MAINPAGE specifies a file in Markdown format that should be used as main
# page. This page will overrule any ``\mainpage`` command in the included
# sources.
#
# IMAGE_DIRS specifies the dirs which contain images that are included in the
# documentation. Dirs can be relative to the current source dir.
#
# EXAMPLE_DIRS specifies the dirs which contain examples that are included in
# the documentation. Dirs can be relative to the current source dir.
#
# QCH_INSTALL_DESTINATION specifies where the generated QCH file will be
# installed.
#
# TAGFILE_INSTALL_DESTINATION specifies where the generated tag file will be
# installed.
#
# NAMESPACE can be used to set a custom namespace <namespace> of the generated
# QCH file. The namepspace is used as the unique id by QHelpEngine (cmp.
# http://doc.qt.io/qt-5/qthelpproject.html#namespace).
# The default namespace is ``<domain>.<basename>``.
# Needs to be used when ORG_DOMAIN is not used.
#
# ORG_DOMAIN can be used to define the organization domain prefix for the
# default namespace of the generated QCH file.
# Needs to be used when NAMESPACE is not used.
#
# LINK_QCHS specifies a list of other QCH targets which should be used for
# creating references to API documenation of code in external libraries.
# For each target <qch> in the list these target properties are expected to be
# defined: DOXYGEN_TAGFILE, QHP_NAMESPACE and QHP_VIRTUALFOLDER.
# If any of these is not existing, <qch> will be ignored.
# Use the macro kdiagram_install_qch_export for exporting a target with these
# properties with the CMake config of a library.
# Any target <qch> can also be one created before in the same buildsystem by
# another call of ``kdiagram_add_qch()``.
#
# LINK_QCHS_VERSIONED does basically the same as LINK_QCHS, but binds the links
# to a certain version.
# For each <qchv> in the list these target properties are expected to be
# defined: DOXYGEN_TAGFILE, QHP_NAMESPACE_VERSIONED and QHP_VIRTUALFOLDER.
# If any of these is not existing, <qchv> will be ignored.
# Use the macro kdiagram_install_qch_export for exporting a target with these
# properties with the CMake config of a library.
# Any <qchv> can also be one created before in the same buildsystem by another
# call of ``kdiagram_add_qch()``.
#
# BLANK_MACROS specifies a list of C/C++ macro names which should be ignored by
# the API dox generation tool and handled as if they resolve to empty strings.
# Examples are export macros only defined in generated files, so whose
# definition might be not available to the tool.
#
# CONFIG_TEMPLATE specifies a custom cmake template file for the config file
# that is created to control the execution of the API dox generation tool.
# The following CMake variables need to be used:
# ECM_DOXYGENQCH_PERL_EXECUTABLE, ECM_DOXYGENQCH_QHELPGENERATOR_EXECUTABLE,
# ECM_DOXYGENQCH_FILEPATH, ECM_DOXYGENQCH_TAGFILE.
# The following CMake variables can be used:
# ECM_DOXYGENQCH_PROJECTNAME, ECM_DOXYGENQCH_PROJECTVERSION,
# ECM_DOXYGENQCH_VIRTUALFOLDER, ECM_DOXYGENQCH_FULLNAMESPACE,
# ECM_DOXYGENQCH_TAGFILES,
# ECM_DOXYGENQCH_WARN_LOGFILE, ECM_DOXYGENQCH_QUIET.
# There is no guarantue that the other CMake variables currently used in the
# default config file template will also be present with the same semantics
# in future versions of this macro.
#
# VERBOSE tells the API dox generation tool to be more verbose about its
# activity.
#
# Example usage:
#
# .. code-block:: cmake
#
#   kdiagram_add_qch(
#       MyLib_QCH
#       OUTPUT_BASENAME MyLib
#       VERSION "0.42.0"
#       ORG_DOMAIN org.myorg
#       SOURCE_DIRS
#           src
#       LINK_QCHS
#           Qt5Core_QCH
#           Qt5Xml_QCH
#           Qt5Gui_QCH
#           Qt5Widgets_QCH
#       BLANK_MACROS
#           MyLib_EXPORT
#           MyLib_DEPRECATED
#       TAGFILE_INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/share/docs/tags
#       QCH_INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/share/docs/qch
#   )
#
# Example usage (with two QCH files, second linking first):
#
# .. code-block:: cmake
#
#   kdiagram_add_qch(
#       MyLib_QCH
#       OUTPUT_BASENAME MyLib
#       VERSION ${MyLib_VERSION}
#       ORG_DOMAIN org.myorg
#       SOURCES ${MyLib_PUBLIC_HEADERS}
#       MD_MAINPAGE src/mylib/README.md
#       LINK_QCHS Qt5Core_QCH
#       TAGFILE_INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/share/docs/tags
#       QCH_INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/share/docs/qch
#   )
#   kdiagram_add_qch(
#       MyOtherLib_QCH
#       OUTPUT_BASENAME MyOtherLib
#       VERSION ${MyOtherLib_VERSION}
#       ORG_DOMAIN org.myorg
#       SOURCES ${MyOtherLib_PUBLIC_HEADERS}
#       MD_MAINPAGE src/myotherlib/README.md
#       LINK_QCHS Qt5Core_QCH MyLib_QCH
#       TAGFILE_INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/share/docs/tags
#       QCH_INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/share/docs/qch
#   )
#
# ::
#
#   kdiagram_install_qch_export(
#       TARGETS [<name> [<name2> [...]]]
#       FILE <file>
#       DESTINATION <dest>
#       [COMPONENT <component>}]
#   )
#
# This macro creates and installs a CMake file <file> which exports the given
# QCH targets <name> etc., so they can be picked up by CMake-based builds of
# other software that also generate QCH files (using ``kdiagram_add_qch()``) and
# which should include links to the QCH files created by the given targets.
# The installed CMake file <file> is expected to be included by the CMake
# config file created for the software the related QCH files are documenting.
#
# TARGETS specifies the QCH targets which should be exported. If a target does
# not exist or does not have all needed properties, a warning will be
# generated and the target skipped.
# This behaviour might change in future versions to result in a fail instead.
#
# FILE specifies the name of the created CMake file, typically with a .cmake
# extension.
#
# DESTINATION specifies the directory on disk to which the file will be
# installed. It usually is the same as the one where the CMake config files
# for this software are installed.
#
# COMPONENT specifies the the installation component name with which the
# install rule is associated.
#
# Example usage:
#
# .. code-block:: cmake
#
#   kdiagram_install_qch_export(
#       TARGETS MyLib_QCH
#       FILE MyLibQCHTargets.cmake
#       DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MyLib"
#       COMPONENT Devel
#   )
#
# Since 5.29.0.

#=============================================================================
# Copyright 2016 Friedrich W. H. Kossebau <kossebau@kde.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# needed to find helper files
get_filename_component(_module_dir ${CMAKE_CURRENT_LIST_FILE} PATH)

# Estimate KDIAGRAM_QTQCH_FULL_INSTALL_DIR
include(KDEInstallDirs) # for KDE_INSTALL_USE_QT_SYS_PATHS & KDE_INSTALL_FULL_DATAROOTDIR
include("${_module_dir}/KDiagramQueryQmake.cmake")
if(KDE_INSTALL_USE_QT_SYS_PATHS)
    query_qmake(qt_docs_dir QT_INSTALL_DOCS)
    set(KDIAGRAM_QTQCH_FULL_INSTALL_DIR "${qt_docs_dir}")
else()
    set(KDIAGRAM_QTQCH_FULL_INSTALL_DIR "${KDE_INSTALL_FULL_DATAROOTDIR}/doc")
endif()

include(CMakeParseArguments)

function(kdiagram_add_qch target_name)
    # Parse arguments
    set(options VERBOSE)
    set(oneValueArgs OUTPUT_BASENAME QCH_INSTALL_DESTINATION TAGFILE_INSTALL_DESTINATION VERSION NAMESPACE MD_MAINPAGE ORG_DOMAIN CONFIG_TEMPLATE)
    set(multiValueArgs SOURCE_DIRS SOURCES IMAGE_DIRS EXAMPLE_DIRS BLANK_MACROS LINK_QCHS LINK_QCHS_VERSIONED)
    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # check required args
    foreach(_arg_name OUTPUT_BASENAME QCH_INSTALL_DESTINATION TAGFILE_INSTALL_DESTINATION VERSION)
        if(NOT DEFINED ARGS_${_arg_name})
            message(FATAL_ERROR "${_arg_name} needs to be defined when calling kdiagram_add_qch")
        endif()
    endforeach()
    if(NOT DEFINED ARGS_SOURCE_DIRS AND NOT DEFINED ARGS_SOURCES AND NOT DEFINED ARGS_CONFIG_TEMPLATE)
        message(FATAL_ERROR "SOURCE_DIRS or SOURCES needs to be defined when calling kdiagram_add_qch")
    endif()
    if(DEFINED ARGS_SOURCE_DIRS AND DEFINED ARGS_SOURCES)
        message(FATAL_ERROR "Either SOURCE_DIRS or SOURCES, not both, needs to be defined when calling kdiagram_add_qch")
    endif()
    if(NOT DEFINED ARGS_ORG_DOMAIN AND NOT DEFINED ARGS_NAMESPACE)
        message(FATAL_ERROR "ORG_DOMAIN or NAMESPACE needs to be defined when calling kdiagram_add_qch")
    endif()

    # create QCH targets for Qt
    # Ideally one day Qt CMake Config files provide these
    if(NOT TARGET Qt5Core_QCH)
        # get Qt version, if any
        find_package(Qt5Core CONFIG QUIET)
        # lookup tag files
        query_qmake(qt_docs_dir QT_INSTALL_DOCS)
        find_path(_qtcoreTagsPath qtcore/qtcore.tags
            PATHS
                ${qt_docs_dir}
        )

        if(Qt5Core_FOUND AND _qtcoreTagsPath)
            string(REPLACE "." "" _version ${Qt5Core_VERSION})
            # TODO: properly find each tag file
            # TODO: complete list of Qt modules
            foreach(_module
                Bluetooth Concurrent Core DBus Gui Location Multimedia MultimediaWidgets
                Network Positioning PrintSupport Qml Quick Sensors SerialPort Sql Svg
                WebEngine WebView Widgets Xml XmlPatterns
            )
                string(TOLOWER ${_module} _lowermodule)

                add_custom_target(Qt5${_module}_QCH)
                set_target_properties(Qt5${_module}_QCH PROPERTIES
                    DOXYGEN_TAGFILE         "${_qtcoreTagsPath}/qt${_lowermodule}/qt${_lowermodule}.tags"
                    QHP_NAMESPACE           "org.qt-project.qt${_lowermodule}"
                    QHP_NAMESPACE_VERSIONED "org.qt-project.qt${_lowermodule}.${_version}"
                    QHP_VIRTUALFOLDER       "qt${_lowermodule}"
                    IMPORTED TRUE
                )
            endforeach()
        endif()
    endif()

    # find required tools
    find_package(Perl)
    set_package_properties(Perl PROPERTIES
        TYPE OPTIONAL
    )
    find_package(Doxygen)
    set_package_properties(Doxygen PROPERTIES
        TYPE OPTIONAL
        DESCRIPTION "Tool for API Documentation generation"
        URL "http://www.doxygen.org/"
    )
    if (DOXYGEN_FOUND AND DOXYGEN_VERSION VERSION_LESS 1.8.13 AND NOT DOXYGEN_PATCHED_JSFILESADDED)
        message(WARNING "Make sure Doxygen is patched with https://github.com/doxygen/doxygen/commit/bf9415698e53d79b, then pass -DDOXYGEN_PATCHED_JSFILESADDED=ON to cmake")
        set(DOXYGEN_FOUND FALSE)
    endif()
    # TODO: use Qt5::qhelpgenerator for Qt >= 5.7.1
    find_program(ECM_DOXYGENQCH_QHELPGENERATOR_EXECUTABLE NAMES qhelpgenerator-qt5 qhelpgenerator)

    # prepare base dirs, working file names and other vars
    set(_qch_file_basename "${ARGS_OUTPUT_BASENAME}.qch")
    set(_tags_file_basename "${ARGS_OUTPUT_BASENAME}.tags")
    set(_qch_buildpath "${CMAKE_CURRENT_BINARY_DIR}/${_qch_file_basename}")
    set(_tags_buildpath "${CMAKE_CURRENT_BINARY_DIR}/${_tags_file_basename}")
    set(_apidox_builddir "${CMAKE_CURRENT_BINARY_DIR}/${ARGS_OUTPUT_BASENAME}_ECMDoxygenQCH")
    if (DEFINED ARGS_NAMESPACE)
        set(_namespace "${ARGS_NAMESPACE}")
    else()
        set(_namespace "${ARGS_ORG_DOMAIN}.${ARGS_OUTPUT_BASENAME}")
    endif()
    string(REPLACE "." "_" _dotLessVersion ${ARGS_VERSION})
    set(_versioned_namespace "${_namespace}.${_dotLessVersion}")
    set(_sources)
    set(_dep_tagfiles)
    set(_dep_qch_targets)

    ### Create doxygen config file
    set(_doxygenconfig_file "${CMAKE_CURRENT_BINARY_DIR}/${ARGS_OUTPUT_BASENAME}_ECMDoxygenQCH.config")
    if (DEFINED ARGS_CONFIG_TEMPLATE)
        set(_doxygenconfig_template_file "${ARGS_CONFIG_TEMPLATE}")
    else()
        set(_doxygenconfig_template_file "${_module_dir}/KDiagramDoxygenQCH.config.in")
    endif()
    # Setup variables used in config file template, ECM_DOXYGENQCH_*
    set(ECM_DOXYGENQCH_OUTPUTDIR "\"${_apidox_builddir}\"")
    set(ECM_DOXYGENQCH_TAGFILE "\"${_tags_buildpath}\"")
    set(ECM_DOXYGENQCH_LAYOUTFILE "\"${_module_dir}/KDiagramDoxygenQCHLayout.xml\"")
    set(ECM_DOXYGENQCH_IMAGEDIRS)
    foreach(_image_DIR IN LISTS ARGS_IMAGE_DIRS)
        if (NOT IS_ABSOLUTE ${_image_DIR})
            set(_image_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${_image_DIR}")
        endif()
        # concat dirs separated by a break, it is no issue that first has also a leading break
        set(ECM_DOXYGENQCH_IMAGEDIRS "${ECM_DOXYGENQCH_IMAGEDIRS} \\\n\"${_image_DIR}\"")
    endforeach()
    set(ECM_DOXYGENQCH_EXAMPLEDIRS)
    foreach(_example_DIR IN LISTS ARGS_EXAMPLE_DIRS)
        if (NOT IS_ABSOLUTE ${_example_DIR})
            set(_example_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${_example_DIR}")
        endif()
        # concat dirs separated by a break, it is no issue that first has also a leading break
        set(ECM_DOXYGENQCH_EXAMPLEDIRS "${ECM_DOXYGENQCH_EXAMPLEDIRS} \\\n\"${_example_DIR}\"")
    endforeach()
    if (ARGS_MD_MAINPAGE)
        if (NOT IS_ABSOLUTE ${ARGS_MD_MAINPAGE})
            set(ARGS_MD_MAINPAGE "${CMAKE_CURRENT_SOURCE_DIR}/${ARGS_MD_MAINPAGE}")
        endif()
        set(ECM_DOXYGENQCH_MAINPAGE_MDFILE "\"${ARGS_MD_MAINPAGE}\"")
    else()
        set(ECM_DOXYGENQCH_MAINPAGE_MDFILE)
    endif()
    set(ECM_DOXYGENQCH_INPUT)
    if (ARGS_SOURCE_DIRS)
        foreach(_source_DIR IN LISTS ARGS_SOURCE_DIRS)
            if (NOT IS_ABSOLUTE ${_source_DIR})
                set(_source_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${_source_DIR}")
            endif()
            # concat dirs separated by a break, it is no issue that first has also a leading break
            set(ECM_DOXYGENQCH_INPUT "${ECM_DOXYGENQCH_INPUT} \\\n\"${_source_DIR}\"")
        endforeach()
        if (ARGS_MD_MAINPAGE)
            set(ECM_DOXYGENQCH_INPUT "${ECM_DOXYGENQCH_INPUT} \\\n\"${ARGS_MD_MAINPAGE}\"")
        endif()
        set(ECM_DOXYGENQCH_FILE_PATTERNS "*.h *.cpp *.hpp *.hh *.cc *.h++ *.c++ *.hxx *.cxx *.dox *.md")
    else()
        foreach(_source IN LISTS ARGS_SOURCES)
            if (NOT IS_ABSOLUTE ${_source})
                set(_source "${CMAKE_CURRENT_SOURCE_DIR}/${_source}")
            endif()
            list(APPEND _sources "${_source}")
        endforeach()
        if (ARGS_MD_MAINPAGE)
            list(FIND _sources ${ARGS_MD_MAINPAGE} _mainpage_index)
            if (_mainpage_index STREQUAL -1)
                list(APPEND _sources "${ARGS_MD_MAINPAGE}")
            endif()
        endif()
        foreach(_source IN LISTS _sources)
            # concat sources separated by a break, it is no issue that first has also a leading break
            set(ECM_DOXYGENQCH_INPUT "${ECM_DOXYGENQCH_INPUT} \\\n\"${_source}\"")
        endforeach()
        set(ECM_DOXYGENQCH_FILE_PATTERNS "")
    endif()

    set(ECM_DOXYGENQCH_PROJECTNAME ${ARGS_OUTPUT_BASENAME})
    file(RELATIVE_PATH _builddirrelative_filepath "${_apidox_builddir}/html"  ${_qch_buildpath})
    set(ECM_DOXYGENQCH_FILEPATH "\"${_builddirrelative_filepath}\"")
    set(ECM_DOXYGENQCH_PROJECTVERSION ${ARGS_VERSION})
    set(ECM_DOXYGENQCH_VIRTUALFOLDER "${ARGS_OUTPUT_BASENAME}")
    set(ECM_DOXYGENQCH_FULLNAMESPACE ${_versioned_namespace})
    set(ECM_DOXYGENQCH_BLANK_MACROS)
    foreach(_macro IN LISTS ARGS_BLANK_MACROS)
        # concat dirs separated by a break, it is no issue that first has also a leading break
        set(ECM_DOXYGENQCH_BLANK_MACROS "${ECM_DOXYGENQCH_BLANK_MACROS} \\\n${_macro}=\"\"")
    endforeach()
    set(ECM_DOXYGENQCH_TAGFILES)
    foreach(_versioned_postfix "" "_VERSIONED")
        foreach(_link_qch IN LISTS ARGS_LINK_QCHS${_versioned_postfix})
            set(_target_usable TRUE)
            if (NOT TARGET ${_link_qch})
                message(STATUS "No such target ${_link_qch} defined when calling kdiagram_add_qch().")
                set(_target_usable FALSE)
            elseif()
                foreach(_propertyname
                    DOXYGEN_TAGFILE
                    QHP_NAMESPACE${_versioned_postfix}
                    QHP_VIRTUALFOLDER
                )
                    if(NOT "${_property}")
                        message(STATUS "No property ${_propertyname} set on ${_link_qch} when calling kdiagram_add_qch().")
                        set(_target_usable FALSE)
                    endif()
                endforeach()
            endif()
            if(_target_usable)
                list(APPEND _dep_qch_targets ${_link_qch})
                get_target_property(_link_qch_tagfile ${_link_qch} DOXYGEN_TAGFILE)
                get_target_property(_link_qch_tagfile_build ${_link_qch} DOXYGEN_TAGFILE_BUILD)
                get_target_property(_link_qch_namespace ${_link_qch} QHP_NAMESPACE${_versioned_postfix})
                get_target_property(_link_qch_virtualfolder ${_link_qch} QHP_VIRTUALFOLDER)
                # if same build, then prefer build version over any installed one
                if (${_link_qch_tagfile_build})
                    set(_link_qch_tagfile ${_link_qch_tagfile_build})
                    list(APPEND _dep_tagfiles "${_link_qch_tagfile}")
                endif()
                set(_tagfile_entry "\"${_link_qch_tagfile}=qthelp://${_link_qch_namespace}/${_link_qch_virtualfolder}/\"")
                # concat dirs separated by a break, it is no issue that first has also a leading break
                set(ECM_DOXYGENQCH_TAGFILES "${ECM_DOXYGENQCH_TAGFILES} \\\n${_tagfile_entry}")
            else()
                message(WARNING "No linking to API dox of ${_link_qch}.")
            endif()
        endforeach()
    endforeach()

    set(ECM_DOXYGENQCH_WARN_LOGFILE "\"${_doxygenconfig_file}.log\"")
    if(ARGS_VERBOSE)
        set(ECM_DOXYGENQCH_QUIET "NO")
    else()
        set(ECM_DOXYGENQCH_QUIET "YES")
    endif()
    set(ECM_DOXYGENQCH_PERL_EXECUTABLE "${PERL_EXECUTABLE}")

    if (NOT DOXYGEN_FOUND)
        message(WARNING "Unable to find the doxygen utility - API dox QCH file will not be generated!")
    elseif(NOT ECM_DOXYGENQCH_QHELPGENERATOR_EXECUTABLE)
        message(WARNING "Unable to find the qhelpgenerator utility - API dox QCH file will not be generated!")
    elseif(NOT PERL_FOUND)
        message(WARNING "Unable to find the perl utility - API dox QCH file will not be generated!")
    else()
        configure_file(
            "${_doxygenconfig_template_file}"
            "${_doxygenconfig_file}"
            @ONLY
        )

        set(_qch_INSTALLPATH ${ARGS_QCH_INSTALL_DESTINATION})
        set(_tags_INSTALLPATH ${ARGS_TAGFILE_INSTALL_DESTINATION})
        file(RELATIVE_PATH _relative_qch_file ${CMAKE_BINARY_DIR}  ${_qch_buildpath})
        file(RELATIVE_PATH _relative_tags_file ${CMAKE_BINARY_DIR}  ${_tags_buildpath})
        add_custom_command(
            OUTPUT ${_qch_buildpath} ${_tags_buildpath}
            COMMENT "Generating ${_relative_qch_file}, ${_relative_tags_file}"
            COMMAND cmake -E remove_directory "${ECM_DOXYGENQCH_OUTPUTDIR}"
            COMMAND cmake -E make_directory "${ECM_DOXYGENQCH_OUTPUTDIR}"
            COMMAND ${DOXYGEN_EXECUTABLE} "${_doxygenconfig_file}"
            DEPENDS ${_doxygenconfig_file} ${_sources} ${_dep_tagfiles} ${_dep_qch_targets}
        )
        add_custom_target(${target_name} ALL DEPENDS ${_qch_buildpath} ${_tags_buildpath})
        set_target_properties(${target_name} PROPERTIES
            DOXYGEN_TAGFILE "${_qch_INSTALLPATH}/${_tags_file_basename}"
            DOXYGEN_TAGFILE_BUILD "${_tags_buildpath}"
            QHP_NAMESPACE "${_namespace}"
            QHP_NAMESPACE_VERSIONED  "${_versioned_namespace}"
            QHP_VIRTUALFOLDER "${ECM_DOXYGENQCH_VIRTUALFOLDER}"
        )

        install(FILES
            ${_qch_buildpath}
            DESTINATION ${_qch_INSTALLPATH}
            COMPONENT Devel
        )

        install(FILES
            ${_tags_buildpath}
            DESTINATION ${_tags_INSTALLPATH}
            COMPONENT Devel
        )
    endif()

endfunction()


function(kdiagram_install_qch_export)
    set(options )
    set(oneValueArgs FILE DESTINATION COMPONENT)
    set(multiValueArgs TARGETS)

    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT DEFINED ARGS_FILE)
        message(FATAL_ERROR "FILE needs to be defined when calling kdiagram_install_qch_export().")
    endif()

    if(NOT DEFINED ARGS_DESTINATION)
        message(FATAL_ERROR "DESTINATION needs to be defined when calling kdiagram_install_qch_export().")
    endif()

    # TARGETS may be empty (and ARGS_TARGETS will not be defined then by cmake_parse_arguments)

    set(_content
"# Generated by kdiagram_install_qch_export()
# Any changes to this file will be overwritten by the next CMake run.
"
    )

    foreach(_target IN LISTS ARGS_TARGETS)
        set(_target_usable TRUE)

        if (NOT TARGET ${_target})
            message(STATUS "No such target ${_target} when calling kdiagram_install_qch_export().")
            set(_target_usable FALSE)
        else()
            foreach(_propertyname
                DOXYGEN_TAGFILE
                QHP_NAMESPACE
                QHP_NAMESPACE_VERSIONED
                QHP_VIRTUALFOLDER
            )
                get_target_property(_property ${_target} ${_propertyname})
                if(NOT _property)
                    message(STATUS "No property ${_propertyname} set on ${_target} when calling kdiagram_install_qch_export(). <${_property}>")
                    set(_target_usable FALSE)
                endif()
            endforeach()
        endif()
        if(_target_usable)
            get_target_property(_tagfile ${_target} DOXYGEN_TAGFILE)
            get_target_property(_namespace ${_target} QHP_NAMESPACE)
            get_target_property(_namespace_versioned ${_target} QHP_NAMESPACE_VERSIONED)
            get_target_property(_virtualfolder ${_target} QHP_VIRTUALFOLDER)
            set(_content "${_content}
if (NOT TARGET ${_target})

add_custom_target(${_target})
set_target_properties(${_target} PROPERTIES
    DOXYGEN_TAGFILE \"${_tagfile}\"
    QHP_NAMESPACE \"${_namespace}\"
    QHP_NAMESPACE_VERSIONED \"${_namespace_versioned}\"
    QHP_VIRTUALFOLDER \"${_virtualfolder}\"
    IMPORTED TRUE
)

endif()
"
            )
        else()
            message(STATUS "No target exported for ${_target}.")
        endif()
    endforeach()

    if (NOT IS_ABSOLUTE ${ARGS_FILE})
        set(ARGS_FILE "${CMAKE_CURRENT_BINARY_DIR}/${ARGS_FILE}")
    endif()

    file(GENERATE
        OUTPUT "${ARGS_FILE}"
        CONTENT "${_content}"
    )

    if (DEFINED ARGS_COMPONENT)
        set(_component COMPONENT ${ARGS_COMPONENT})
    endif()
    install(
        FILES "${ARGS_FILE}"
        DESTINATION "${ARGS_DESTINATION}"
        ${_component}
    )

endfunction()
