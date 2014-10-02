#---
# File: FindGoogleBenchmark.cmake
#
# Find the Google Benchmark includes and libraries.
#
# This module defines:
# GBENCHMARK_INCLUDE_DIR - where to find benchmark.h.
# GBENCHMARK_LIBRARY     - libbenchmark.a library.
# GBENCHMARK_FOUND       - true if found, false if one of the above are not found.
#---

file (GLOB_RECURSE GBENCHMARK_H_HEADER ${PROJECT_SOURCE_DIR}/*benchmark.h)
if    (NOT GBENCHMARK_H_HEADER STREQUAL "")
    get_filename_component (GBENCHMARK_INCLUDE_DIR ${GBENCHMARK_H_HEADER} DIRECTORY)
    string (REGEX REPLACE "/benchmark$" "" GBENCHMARK_INCLUDE_DIR ${GBENCHMARK_INCLUDE_DIR})
endif (NOT GBENCHMARK_H_HEADER STREQUAL "")


file (GLOB_RECURSE GBENCHMARK_LIBRARY ${PROJECT_SOURCE_DIR}/*libbenchmark.a)


include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (
    GBENCHMARK DEFAULT_MSG
    GBENCHMARK_LIBRARY
    GBENCHMARK_INCLUDE_DIR
)


if (GBENCHMARK_FOUND)
    if (NOT GBENCHMARK_FIND_QUIETLY)
        message(STATUS "Google benchmark library is found.")
    endif (NOT GBENCHMARK_FIND_QUIETLY)
else (GBENCHMARK_FOUND)
    if(NOT GBENCHMARK_FIND_QUIETLY)
        message (WARNING "Could not find Google benchmark library!")
    endif (NOT GBENCHMARK_FIND_QUIETLY)
endif (GBENCHMARK_FOUND)

if (NOT GBENCHMARK_FIND_QUIETLY)
    message (STATUS "GBENCHMARK_INCLUDE_DIR: ${GBENCHMARK_INCLUDE_DIR}")
    message (STATUS "GBENCHMARK_LIBRARY    : ${GBENCHMARK_LIBRARY}")
endif (NOT GBENCHMARK_FIND_QUIETLY)
