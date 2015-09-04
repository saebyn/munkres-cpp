find_package (Boost     COMPONENTS      system      REQUIRED)

enable_testing ()

# Test suites.
set (CMAKE_CXX_FLAGS "-std=c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set (CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -O0 -ggdb3 -DDEBUG")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
set (CMAKE_SHARED_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

include_directories (${GTEST_INCLUDE_DIRS})

set (
    MunkresCppTest_SOURCES
    ${PROJECT_SOURCE_DIR}/tests/munkrestest.cpp
    ${PROJECT_SOURCE_DIR}/tests/matrixtest.cpp
    ${PROJECT_SOURCE_DIR}/tests/adapters/raw_2d_arraytest.cpp
    ${PROJECT_SOURCE_DIR}/tests/adapters/std_2d_arraytest.cpp
    ${PROJECT_SOURCE_DIR}/tests/adapters/std_2d_vectortest.cpp
    ${PROJECT_SOURCE_DIR}/tests/adapters/boost_matrixtest.cpp
)
add_executable (munkrestest ${MunkresCppLib_SOURCES} ${MunkresCppTest_SOURCES})
target_link_libraries (munkrestest ${GTEST_BOTH_LIBRARIES} gcov pthread)
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
