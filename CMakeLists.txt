# Common variables.
cmake_minimum_required  (VERSION 2.8)
project                 (MunkresCpp)
set (MunkresCpp_VERSION_MAJOR 0)
set (MunkresCpp_VERSION_MINOR 1)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")


if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message (FATAL_ERROR "Prevented in-tree build. This is bad practice.")
endif (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wmissing-include-dirs -Wundef -Wfloat-equal -Wshadow -Wunsafe-loop-optimizations")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdouble-promotion -Winit-self -Wvector-operation-performance -Wnoexcept -Weffc++ -Wstrict-null-sentinel")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Wsign-promo")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvla -Winvalid-pch -Winline -Wredundant-decls")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op -Wcast-align")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual -Wpointer-arith -Wtrampolines")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wzero-as-null-pointer-constant")
set (CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -O0 -ggdb3 -DDEBUG")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")


include_directories (${PROJECT_SOURCE_DIR}/src)


# Library.
set (MunkresCppLib_SOURCES ${PROJECT_SOURCE_DIR}/src/munkres.cpp)
add_library (munkres SHARED STATIC ${MunkresCppLib_SOURCES})


# Binary example
set (MunkresCppBin_SOURCES ${PROJECT_SOURCE_DIR}/examples/main.cpp)
add_executable (munkres.bin ${MunkresCppBin_SOURCES})
target_link_libraries (munkres.bin munkres)


# Static code analyse.
set (CppCheck_REPORT ${PROJECT_BINARY_DIR}/cppcheck.report)
add_custom_command (
    OUTPUT  ${CppCheck_REPORT}
    COMMAND cppcheck ${MunkresCppLib_SOURCES} ${MunkresCppBin_SOURCES} -I${PROJECT_SOURCE_DIR}/src -I${PROJECT_SOURCE_DIR} --enable=all --force --inconclusive &>cppcheck.report
)
add_custom_target  (cppcheck DEPENDS ${CppCheck_REPORT})
set_directory_properties (PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CppCheck_REPORT})


# Testing
find_package (GTest)
if (GTEST_FOUND)
    add_subdirectory (tests)
endif ()


# Benchmarking
add_subdirectory (benchmarks)
