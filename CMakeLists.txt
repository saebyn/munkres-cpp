# Common variables.
cmake_minimum_required  (VERSION 2.8)
project                 (munkres-cpp)
set (munkres-cpp_VERSION_MAJOR 2)
set (munkres-cpp_VERSION_MINOR 0)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set (CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -O0 -ggdb3 -DDEBUG")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")

# Set custom macro for provide Design By Contract (by default is disabled).
if (DEFINED DBC_MODE)
    add_definitions (-DDEBUG_WITH_DBC=${DBC_MODE})
endif ()

include_directories (${PROJECT_SOURCE_DIR}/src)

# Sources (nothing).
set (
    MunkresCpp_SOURCES
)

# Headers.
set (
    MunkresCpp_HEADERS
    ${PROJECT_SOURCE_DIR}/src/matrix.h
    ${PROJECT_SOURCE_DIR}/src/munkres.h
)

# Library.
add_library (
    munkres INTERFACE
)

install (FILES ${MunkresCpp_HEADERS} DESTINATION include PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)


# Binary example
set (MunkresCppBin_SOURCES ${PROJECT_SOURCE_DIR}/examples/main.cpp)
add_executable (munkres.bin EXCLUDE_FROM_ALL ${MunkresCppBin_SOURCES})
target_link_libraries (munkres.bin munkres)
add_custom_target (example)
add_dependencies  (example munkres.bin)


option (MUNKRESCPP_DEVEL_MODE "Configure project in development mode." OFF)
if (MUNKRESCPP_DEVEL_MODE)
    # Enable the ExternalProject_Add directive.
    # Which used for getting external tools for the Project.
    include (ExternalProject)


    # Testing
    add_subdirectory (tests)


    # Benchmarking
    add_subdirectory (benchmarks)


    # Custom target to build everything.
    add_custom_target  (full)
    add_dependencies (
        full
        munkres
        example
        tests
        benchmarks
    )


    # Static code analyse.
    set (CppCheck_REPORT ${PROJECT_BINARY_DIR}/cppcheck.report)
    add_custom_command (
        OUTPUT  ${CppCheck_REPORT}
        COMMAND cppcheck ${MunkresCpp_HEADERS} ${MunkresCppBin_SOURCES} -I${PROJECT_SOURCE_DIR}/src -I${PROJECT_SOURCE_DIR} --enable=all --force --inconclusive > cppcheck.report 2>&1
    )
    add_custom_target  (cppcheck DEPENDS ${CppCheck_REPORT})
    set_directory_properties (PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CppCheck_REPORT})

    # Code format.
    set (UNCRUSTIFY_LST ${PROJECT_BINARY_DIR}/uncrustify.lst)
    set (UNCRUSTIFY_CFG ${PROJECT_SOURCE_DIR}/uncrustify.cfg)
    add_custom_target (
        beauty
        COMMAND find ${PROJECT_SOURCE_DIR} -name '*.cpp' -o -name '*.h' | grep -v ${PROJECT_BINARY_DIR} > ${UNCRUSTIFY_LST}
        COMMAND uncrustify -c ${UNCRUSTIFY_CFG} -F ${UNCRUSTIFY_LST} --no-backup -l CPP
    )
endif ()
