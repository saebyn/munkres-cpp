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
    ${PROJECT_SOURCE_DIR}/src/munkres-cpp/matrix.h
    ${PROJECT_SOURCE_DIR}/src/munkres-cpp/matrix_base.h
    ${PROJECT_SOURCE_DIR}/src/munkres-cpp/utils.h
    ${PROJECT_SOURCE_DIR}/src/munkres-cpp/munkres.h
    ${PROJECT_SOURCE_DIR}/src/munkres-cpp/adapters/matrix_armadillo.h
    ${PROJECT_SOURCE_DIR}/src/munkres-cpp/adapters/matrix_boost.h
    ${PROJECT_SOURCE_DIR}/src/munkres-cpp/adapters/matrix_eigen.h
    ${PROJECT_SOURCE_DIR}/src/munkres-cpp/adapters/matrix_opencv.h
    ${PROJECT_SOURCE_DIR}/src/munkres-cpp/adapters/matrix_qt.h
    ${PROJECT_SOURCE_DIR}/src/munkres-cpp/adapters/matrix_std_2d_vector.h
)

# Library.
add_library (
    munkres INTERFACE
)

install (DIRECTORY ${PROJECT_SOURCE_DIR}/src/ DESTINATION include FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)


# Binary examples
add_executable (example_01 EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/example_01.cpp)
add_executable (example_02 EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/example_02.cpp)
add_executable (example_03 EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/example_03.cpp)
add_executable (example_04 EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/example_04.cpp)
add_executable (example_05 EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/example_05.cpp)
add_executable (example_06 EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/example_06.cpp)
add_custom_target (examples)
add_dependencies  (
    examples
    example_01
    example_02
    example_03
    example_04
    example_05
    example_06
)


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
        examples
        tests
        benchmarks
        warnings
    )


    # Static code analyse.
    set (CppCheck_REPORT ${PROJECT_BINARY_DIR}/cppcheck.report)
    add_custom_command (
        OUTPUT  ${CppCheck_REPORT}
        COMMAND cppcheck ${MunkresCpp_HEADERS} ${MunkresCppBin_SOURCES} -I${PROJECT_SOURCE_DIR}/src -I${PROJECT_SOURCE_DIR} --enable=all --force --inconclusive > cppcheck.report 2>&1
    )
    add_custom_target  (cppcheck DEPENDS ${CppCheck_REPORT})
    set_directory_properties (PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CppCheck_REPORT})

    # Dummy target with special warning options for more attentive checking.
    set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Wmissing-include-dirs -Wundef -Wfloat-equal -Wunsafe-loop-optimizations")
    set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Wdouble-promotion -Winit-self -Wvector-operation-performance -Wnoexcept -Weffc++ -Wstrict-null-sentinel")
    set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Woverloaded-virtual -Wsign-promo")
    set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Wvla -Winvalid-pch -Winline -Wredundant-decls")
    set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Wlogical-op -Wcast-align")
    set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Wcast-qual -Wpointer-arith -Wtrampolines")
    set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Wold-style-cast")
    set_source_files_properties (
        ${PROJECT_SOURCE_DIR}/tests/warnings_test.cpp
        ${warning_source}
        PROPERTIES COMPILE_FLAGS ${SPECIAL_CXX_WARNING_FLAGS}
    )
    add_executable (munkres_dummy.bin EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/tests/warnings_test.cpp)
    add_custom_target (warnings)
    add_dependencies  (warnings munkres_dummy.bin)

    # Code format.
    set (UNCRUSTIFY_LST ${PROJECT_BINARY_DIR}/uncrustify.lst)
    set (UNCRUSTIFY_CFG ${PROJECT_SOURCE_DIR}/uncrustify.cfg)
    add_custom_target (
        beauty
        COMMAND find ${PROJECT_SOURCE_DIR} -name '*.cpp' -o -name '*.h' | grep -v ${PROJECT_BINARY_DIR} > ${UNCRUSTIFY_LST}
        COMMAND uncrustify -c ${UNCRUSTIFY_CFG} -F ${UNCRUSTIFY_LST} --no-backup -l CPP
    )
endif ()
