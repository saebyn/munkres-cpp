# Common variables.
CMAKE_MINIMUM_REQUIRED  (VERSION 2.8)
PROJECT                 (MunkresCpp)
SET (MunkresCpp_VERSION_MAJOR 0)
SET (MunkresCpp_VERSION_MINOR 1)
SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMakeModules")


SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wmissing-include-dirs -Wundef -Wfloat-equal -Wshadow -Wunsafe-loop-optimizations")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdouble-promotion -Winit-self -Wvector-operation-performance -Wnoexcept -Weffc++ -Wstrict-null-sentinel")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Wsign-promo")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvla -Winvalid-pch -Winline -Wredundant-decls")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op -Wcast-align")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual -Wpointer-arith -Wtrampolines")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wzero-as-null-pointer-constant")
SET (CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -O0 -ggdb3 -DDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")

INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/src)


# Library.
SET (MunkresCppLib_SOURCES ${PROJECT_SOURCE_DIR}/src/munkres.cpp)
ADD_LIBRARY (munkres SHARED STATIC ${MunkresCppLib_SOURCES})


# Binary example
SET (MunkresCppBin_SOURCES ${PROJECT_SOURCE_DIR}/examples/main.cpp)
ADD_EXECUTABLE (munkres.bin ${MunkresCppBin_SOURCES})
TARGET_LINK_LIBRARIES (munkres.bin munkres)


# Static code analyse.
SET (CppCheck_REPORT ${PROJECT_BINARY_DIR}/cppcheck.report)
ADD_CUSTOM_COMMAND (
    OUTPUT  ${CppCheck_REPORT}
    COMMAND cppcheck ${MunkresCppLib_SOURCES} ${MunkresCppBin_SOURCES} -I${PROJECT_SOURCE_DIR}/src -I${PROJECT_SOURCE_DIR} --enable=all --force --inconclusive &>cppcheck.report
)
ADD_CUSTOM_TARGET  (cppcheck DEPENDS ${CppCheck_REPORT})
SET_DIRECTORY_PROPERTIES (PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CppCheck_REPORT})


# Testing
FIND_PACKAGE (GTest)
IF (GTEST_FOUND)
    ADD_SUBDIRECTORY (tests)
ENDIF ()
