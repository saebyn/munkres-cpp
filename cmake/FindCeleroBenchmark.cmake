#---
# File: FindCeleroBenchmark.cmake
#
# Find the Celero includes and libraries.
#
# This module defines:
# CELERO_INCLUDE_DIR - where to find Celero.h.
# CELERO_LIBRARY     - libcelero.so library.
# CELERO_FOUND       - true if found, false if one of the above are not found.
#---


file (GLOB_RECURSE CELERO_H_HEADER ${PROJECT_SOURCE_DIR}/*/Celero.h)
if    (NOT CELERO_H_HEADER STREQUAL "")
    get_filename_component (CELERO_INCLUDE_DIR ${CELERO_H_HEADER} DIRECTORY)
    string (REGEX REPLACE "/celero$" "" CELERO_INCLUDE_DIR ${CELERO_INCLUDE_DIR})
endif (NOT CELERO_H_HEADER STREQUAL "")


file (GLOB_RECURSE CELERO_LIBRARY ${PROJECT_SOURCE_DIR}/*libcelero.so)


include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (
    CELERO DEFAULT_MSG
    CELERO_LIBRARY
    CELERO_INCLUDE_DIR
)


if (CELERO_FOUND)
    if (NOT CELERO_FIND_QUIETLY)
        message(STATUS "Celero benchmark library is found.")
    endif (NOT CELERO_FIND_QUIETLY)
else (CELERO_FOUND)
    if(NOT CELERO_FIND_QUIETLY)
        message (WARNING "Could not find Celero benchmark library!")
    endif (NOT CELERO_FIND_QUIETLY)
endif (CELERO_FOUND)

if (NOT CELERO_FIND_QUIETLY)
    message (STATUS "CELERO_INCLUDE_DIR: ${CELERO_INCLUDE_DIR}")
    message (STATUS "CELERO_LIBRARY    : ${CELERO_LIBRARY}")
endif (NOT CELERO_FIND_QUIETLY)
