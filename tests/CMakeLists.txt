find_package (Boost     COMPONENTS      system      REQUIRED)

enable_testing ()

# Framework for writing tests.
ExternalProject_Add (
    googletest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    UPDATE_COMMAND cd ${PROJECT_BINARY_DIR}/googletest && mv googletest gtest && mv gtest/googletest .
    CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Release"
    SOURCE_DIR "${PROJECT_BINARY_DIR}/googletest/googletest"
    BINARY_DIR "${PROJECT_BINARY_DIR}/googletest/googletest"
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
set_target_properties (googletest PROPERTIES EXCLUDE_FROM_ALL TRUE)
set (GTEST_ROOT "${PROJECT_BINARY_DIR}/googletest/googletest")
set (GTEST_FOUND true)
set (GTEST_INCLUDE_DIRS "${PROJECT_BINARY_DIR}/googletest/googletest/include")
set (GTEST_LIBRARIES "${PROJECT_BINARY_DIR}/googletest/googletest/libgtest.a")
set (GTEST_MAIN_LIBRARIES "${PROJECT_BINARY_DIR}/googletest/googletest/libgtest_main.a")
set (GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

include_directories (${GTEST_INCLUDE_DIRS})

# Special flags fo generating code coverage.
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set (CMAKE_SHARED_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

# Special warning options for more attentive checking.
set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Wmissing-include-dirs -Wundef -Wfloat-equal -Wunsafe-loop-optimizations")
set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Wdouble-promotion -Winit-self -Wvector-operation-performance -Wnoexcept -Weffc++ -Wstrict-null-sentinel")
set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Woverloaded-virtual -Wsign-promo")
set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Wvla -Winvalid-pch -Winline -Wredundant-decls")
set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Wlogical-op -Wcast-align")
set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Wcast-qual -Wpointer-arith -Wtrampolines")
set (SPECIAL_CXX_WARNING_FLAGS "${SPECIAL_CXX_WARNING_FLAGS} -Wold-style-cast")

set_source_files_properties (
    ${MunkresCppLib_SOURCES}
    PROPERTIES COMPILE_FLAGS ${SPECIAL_CXX_WARNING_FLAGS}
)


# Test suites.
set (
    MunkresCppTest_SOURCES
    ${PROJECT_SOURCE_DIR}/tests/munkrestest.cpp
    ${PROJECT_SOURCE_DIR}/tests/matrixtest.cpp
    ${PROJECT_SOURCE_DIR}/tests/adapters/std_2d_arraytest.cpp
    ${PROJECT_SOURCE_DIR}/tests/adapters/std_2d_vectortest.cpp
    ${PROJECT_SOURCE_DIR}/tests/adapters/boost_matrixtest.cpp
)
add_executable (munkrestest EXCLUDE_FROM_ALL ${MunkresCppLib_SOURCES} ${MunkresCppTest_SOURCES})
target_link_libraries (munkrestest ${GTEST_BOTH_LIBRARIES} gcov pthread)
add_custom_target (tests)
add_dependencies  (tests munkrestest)
add_dependencies  (munkrestest googletest)
add_test (MunkresCppTest muknrestest)


# Test coverage report.
set (Coverage_REPORT ${PROJECT_BINARY_DIR}/coverage.info)
set (Coverage_DIR    ${PROJECT_BINARY_DIR}/coverage)
add_custom_command (
    OUTPUT  ${Coverage_REPORT}
    COMMAND lcov -q -c -f -b . -d ${PROJECT_BINARY_DIR}/tests -o ${Coverage_REPORT}
    COMMAND lcov -e ${Coverage_REPORT} '${PROJECT_SOURCE_DIR}/src/*' -o ${Coverage_REPORT}
    COMMAND genhtml ${Coverage_REPORT} --legend --demangle-cpp -f -q -o ${Coverage_DIR}
    DEPENDS munkrestest
)
add_custom_target (coverage DEPENDS ${Coverage_REPORT})


# Adding test coverage artifacts to the "make clean" rule.
macro (determine_coverage_data Sources TestName Artifacts Suffix)
set (CoverageDirectory "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${TestName}.dir")
foreach (File ${Sources})
    string (REGEX MATCH "^${CMAKE_CURRENT_SOURCE_DIR}*" Directory "${File}")
    if    (Directory STREQUAL CMAKE_CURRENT_SOURCE_DIR)
        string (REGEX REPLACE "^${CMAKE_CURRENT_SOURCE_DIR}*" "${CoverageDirectory}" File "${File}")
    else  (Directory STREQUAL CMAKE_CURRENT_SOURCE_DIR)
        string (REGEX REPLACE "/" ";" A "${CMAKE_CURRENT_SOURCE_DIR}")
        string (REGEX REPLACE "/" ";" B "${File}")
        list (LENGTH A DeepDirectory)
        list (LENGTH B DeepFile)
        set (File "${CoverageDirectory}")
        set (I 1)
        while    (I less DeepDirectory)
            list (GET A ${I} AI)
            list (GET B ${I} BI)
            if    (AI STREQUAL BI)
                math (EXPR I "${I} + 1")
            else  (AI STREQUAL BI)
                math (EXPR DeepDiff "${DeepFile} - ${I} - 1")
                while    (DeepDiff GREATER 0)
                    set (File "${File}/__")
                    math (EXPR DeepDiff "${DeepDiff} - 1")
                endwhile (DeepDiff GREATER 0)
                while    (I less DeepFile)
                    list (GET B ${I} BI)
                    set (File "${File}/${BI}")
                    math (EXPR I "${I} + 1")
                endwhile (I less DeepFile)
            endif (AI STREQUAL BI)
        endwhile (I less DeepDirectory)
    endif (Directory STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set (${Artifacts} ${${Artifacts}} "${File}${Suffix}")
endforeach (File)
endmacro (determine_coverage_data)

determine_coverage_data ("${MunkresCppTest_SOURCES};${MunkresCppLib_SOURCES}" munkrestest Coverage_GCNO ".gcno")
determine_coverage_data ("${MunkresCppTest_SOURCES};${MunkresCppLib_SOURCES}" munkrestest Coverage_GCDA ".gcda")

list (APPEND Coverage_DATA "${Coverage_REPORT}")
list (APPEND Coverage_DATA "${Coverage_DIR}")
list (APPEND Coverage_DATA "${Coverage_GCNO}")
list (APPEND Coverage_DATA "${Coverage_GCDA}")
set_directory_properties (PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${Coverage_DATA}")
