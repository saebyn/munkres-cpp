# Common variables.
cmake_minimum_required  (VERSION 2.8)
project                 (munkres-cpp)
set (munkres-cpp_VERSION_MAJOR 0)
set (munkres-cpp_VERSION_MINOR 1)


# Getting external tools which used by the Project.

# Enable the ExternalProject_Add directive.
include (ExternalProject)

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
set (GTEST_ROOT "${PROJECT_BINARY_DIR}/googletest/googletest")
set (GTEST_FOUND true)
set (GTEST_INCLUDE_DIRS "${PROJECT_BINARY_DIR}/googletest/googletest/include")
set (GTEST_LIBRARIES "${PROJECT_BINARY_DIR}/googletest/googletest/libgtest.a")
set (GTEST_MAIN_LIBRARIES "${PROJECT_BINARY_DIR}/googletest/googletest/libgtest_main.a")
set (GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

# Microbenchmarking tools.
# Google Benchmark.
ExternalProject_Add (
    benchmark
    GIT_REPOSITORY "https://github.com/google/benchmark.git"
    CMAKE_ARGS "-DBENCHMARK_ENABLE_TESTING=OFF;-DCMAKE_BUILD_TYPE=Release"
    SOURCE_DIR "${PROJECT_BINARY_DIR}/benchmark"
    BINARY_DIR "${PROJECT_BINARY_DIR}/benchmark"
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
set (GBENCHMARK_FOUND true)
set (GBENCHMARK_INCLUDE_DIR "${PROJECT_BINARY_DIR}/benchmark/include")
set (GBENCHMARK_LIBRARY "${PROJECT_BINARY_DIR}/benchmark/src/libbenchmark.a")

# Celero.
ExternalProject_Add (
    Celero
    GIT_REPOSITORY "https://github.com/DigitalInBlue/Celero.git"
    CMAKE_ARGS "-DCELERO_ENABLE_EXPERIMENTS=OFF;-DCMAKE_BUILD_TYPE=Release"
    SOURCE_DIR "${PROJECT_BINARY_DIR}/Celero"
    BINARY_DIR "${PROJECT_BINARY_DIR}/CeleroBuild"
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
set (CELERO_FOUND true)
set (CELERO_INCLUDE_DIR "${PROJECT_BINARY_DIR}/Celero/include")
set (CELERO_LIBRARY "${PROJECT_BINARY_DIR}/CeleroBuild/libcelero.so")

# Hayai.
ExternalProject_Add (
    hayai
    GIT_REPOSITORY "https://github.com/nickbruun/hayai.git"
    SOURCE_DIR "${PROJECT_BINARY_DIR}/hayai"
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
set (HAYAI_FOUND true)
set (HAYAI_INCLUDE_DIR "${PROJECT_BINARY_DIR}/hayai/src")


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-include-dirs -Wundef -Wfloat-equal -Wunsafe-loop-optimizations")
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
    COMMAND cppcheck ${MunkresCppLib_SOURCES} ${MunkresCppBin_SOURCES} -I${PROJECT_SOURCE_DIR}/src -I${PROJECT_SOURCE_DIR} --enable=all --force --inconclusive > cppcheck.report 2>&1
)
add_custom_target  (cppcheck DEPENDS ${CppCheck_REPORT})
set_directory_properties (PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CppCheck_REPORT})


# Testing
add_subdirectory (tests)


# Benchmarking
add_subdirectory (benchmarks)

