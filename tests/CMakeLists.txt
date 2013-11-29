# Test suite generating and building.
SET (CMAKE_CXX_FLAGS "-std=c++11")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
SET (CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -O0 -ggdb3 -DDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
SET (CMAKE_SHARED_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

SET (
    MunkresCppTest_SOURCES
    ${PROJECT_SOURCE_DIR}/tests/munkrestest.cpp
)
ADD_EXECUTABLE (munkrestest ${MunkresCppLib_SOURCES} ${MunkresCppTest_SOURCES})
TARGET_LINK_LIBRARIES (munkrestest gtest gtest_main gcov pthread)
ENABLE_TESTING ()
ADD_TEST (MunkresCppTest muknrestest)



# Test coverage report.
SET (Coverage_REPORT ${PROJECT_BINARY_DIR}/coverage.info)
SET (Coverage_DIR    ${PROJECT_BINARY_DIR}/coverage)
ADD_CUSTOM_COMMAND (
    OUTPUT  ${Coverage_REPORT}
    COMMAND lcov -q -c -f -b . -d ${PROJECT_BINARY_DIR}/tests -o ${Coverage_REPORT}
    COMMAND lcov -e ${Coverage_REPORT} '${PROJECT_SOURCE_DIR}/src/*' -o ${Coverage_REPORT}
    COMMAND genhtml ${Coverage_REPORT} --legend --demangle-cpp -f -q -o ${Coverage_DIR}
    DEPENDS munkrestest
)
ADD_CUSTOM_TARGET (coverage DEPENDS ${Coverage_REPORT})
FILE (GLOB_RECURSE Coverage_GCNO ${PROJECT_BINARY_DIR}/*.gcno)
FILE (GLOB_RECURSE Coverage_GCDA ${PROJECT_BINARY_DIR}/*.gcda)
LIST (APPEND Coverage_DATA "${Coverage_REPORT}")
LIST (APPEND Coverage_DATA "${Coverage_DIR}")
LIST (APPEND Coverage_DATA "${Coverage_GCNO}")
LIST (APPEND Coverage_DATA "${Coverage_GCDA}")
SET_DIRECTORY_PROPERTIES (PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${Coverage_DATA}")
