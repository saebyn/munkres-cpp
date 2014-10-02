#---
# File: FindHayaiBenchmark.cmake
#
# Find the Hayai includes.
#
# This module defines:
# HAYAI_INCLUDE_DIR - where to find hayai.hpp.
# HAYAI_FOUND       - true if found, false if one of the above are not found.
#---


file (GLOB_RECURSE HAYAI_H_HEADER ${PROJECT_SOURCE_DIR}/*/hayai.hpp)
if    (NOT HAYAI_H_HEADER STREQUAL "")
    get_filename_component (HAYAI_INCLUDE_DIR ${HAYAI_H_HEADER} DIRECTORY)
endif (NOT HAYAI_H_HEADER STREQUAL "")


include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (
    HAYAI DEFAULT_MSG
    HAYAI_INCLUDE_DIR
)


if (HAYAI_FOUND)
    if (NOT HAYAI_FIND_QUIETLY)
        message(STATUS "Hayai benchmark is found.")
    endif (NOT HAYAI_FIND_QUIETLY)
else (HAYAI_FOUND)
    if(NOT HAYAI_FIND_QUIETLY)
        message (WARNING "Could not find Hayai benchmark!")
    endif (NOT HAYAI_FIND_QUIETLY)
endif (HAYAI_FOUND)

if (NOT HAYAI_FIND_QUIETLY)
    message (STATUS "HAYAI_INCLUDE_DIR: ${HAYAI_INCLUDE_DIR}")
endif (NOT HAYAI_FIND_QUIETLY)
