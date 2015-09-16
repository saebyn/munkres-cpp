# Common variable.
include_directories (${PROJECT_SOURCE_DIR}/benchmarks/tools/generator)


# Benchmark based on the Google benchmark Framework.
ExternalProject_Add (
    benchmark
    GIT_REPOSITORY "https://github.com/google/benchmark.git"
    CMAKE_ARGS "-DBENCHMARK_ENABLE_TESTING=OFF;-DCMAKE_BUILD_TYPE=Release"
    SOURCE_DIR "${PROJECT_BINARY_DIR}/benchmark"
    BINARY_DIR "${PROJECT_BINARY_DIR}/benchmark"
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
set_target_properties (benchmark PROPERTIES EXCLUDE_FROM_ALL TRUE)
set (GBENCHMARK_FOUND true)
set (GBENCHMARK_INCLUDE_DIR "${PROJECT_BINARY_DIR}/benchmark/include")
set (GBENCHMARK_LIBRARY "${PROJECT_BINARY_DIR}/benchmark/src/libbenchmark.a")

set (MunkresCppBenchmarkGoogle_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_google.cpp)
add_executable (munkresbenchmark_google.bin EXCLUDE_FROM_ALL ${MunkresCppBenchmarkGoogle_SOURCES})
include_directories (${GBENCHMARK_INCLUDE_DIR})
target_link_libraries (munkresbenchmark_google.bin munkres ${GBENCHMARK_LIBRARY} pthread)
add_dependencies (munkresbenchmark_google.bin benchmark)


# Benchmark based on the hayai Framework.
ExternalProject_Add (
    hayai
    GIT_REPOSITORY "https://github.com/nickbruun/hayai.git"
    SOURCE_DIR "${PROJECT_BINARY_DIR}/hayai"
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
set_target_properties (hayai PROPERTIES EXCLUDE_FROM_ALL TRUE)
set (HAYAI_FOUND true)
set (HAYAI_INCLUDE_DIR "${PROJECT_BINARY_DIR}/hayai/src")

set (MunkresCppBenchmarkHayai_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_hayai.cpp)
add_executable (munkresbenchmark_hayai.bin EXCLUDE_FROM_ALL ${MunkresCppBenchmarkHayai_SOURCES})
include_directories (${HAYAI_INCLUDE_DIR})
target_link_libraries (munkresbenchmark_hayai.bin munkres)
add_dependencies (munkresbenchmark_hayai.bin hayai)


# Benchmark based on the Celero Framework.
ExternalProject_Add (
    Celero
    GIT_REPOSITORY "https://github.com/DigitalInBlue/Celero.git"
    CMAKE_ARGS "-DCELERO_ENABLE_EXPERIMENTS=OFF;-DCMAKE_BUILD_TYPE=Release"
    SOURCE_DIR "${PROJECT_BINARY_DIR}/Celero"
    BINARY_DIR "${PROJECT_BINARY_DIR}/CeleroBuild"
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
set_target_properties (Celero PROPERTIES EXCLUDE_FROM_ALL TRUE)
set (CELERO_FOUND true)
set (CELERO_INCLUDE_DIR "${PROJECT_BINARY_DIR}/Celero/include")
set (CELERO_LIBRARY "${PROJECT_BINARY_DIR}/CeleroBuild/libcelero.so")

set (MunkresCppBenchmarkCelero_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_celero.cpp)
add_executable (munkresbenchmark_celero.bin EXCLUDE_FROM_ALL ${MunkresCppBenchmarkCelero_SOURCES})
include_directories (${CELERO_INCLUDE_DIR})
target_link_libraries (munkresbenchmark_celero.bin munkres ${CELERO_LIBRARY})
add_dependencies (munkresbenchmark_celero.bin Celero)


# Benchmark based on the RDTSC.
set (MunkresCppBenchmarkRdtsc_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_rdtsc.cpp)
add_executable (munkresbenchmark_rdtsc.bin EXCLUDE_FROM_ALL ${MunkresCppBenchmarkRdtsc_SOURCES})
target_link_libraries (munkresbenchmark_rdtsc.bin munkres)


# Test for generate profiler (gprof) data.
set (MunkresCppBenchmarkGprof_SOURCES
    ${PROJECT_SOURCE_DIR}/src/munkres.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main_gprof.cpp
)
add_executable (munkresbenchmark_gprof.bin EXCLUDE_FROM_ALL ${MunkresCppBenchmarkGprof_SOURCES})
set_target_properties (munkresbenchmark_gprof.bin PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -pg" LINK_FLAGS "-pg")


# Prevent launch tests before will be generated test data set.
set (BenchmarkDataSet ${PROJECT_BINARY_DIR}/matrices.txt)
add_custom_command (
    OUTPUT ${BenchmarkDataSet}
    COMMAND cd ${PROJECT_BINARY_DIR} && ./benchmarks/tools/generator/matrixgenerator.bin 20
)
add_custom_target (generate_benchmark_dataset DEPENDS ${BenchmarkDataSet})
add_dependencies (generate_benchmark_dataset matrixgenerator.bin)

add_dependencies (munkresbenchmark_google.bin generate_benchmark_dataset)
add_dependencies (munkresbenchmark_hayai.bin  generate_benchmark_dataset)
add_dependencies (munkresbenchmark_celero.bin generate_benchmark_dataset)
add_dependencies (munkresbenchmark_rdtsc.bin  generate_benchmark_dataset)
add_dependencies (munkresbenchmark_gprof.bin  generate_benchmark_dataset)


add_custom_target  (benchmarks)
add_dependencies (
    benchmarks
    munkresbenchmark_google.bin
    munkresbenchmark_celero.bin
    munkresbenchmark_hayai.bin
    munkresbenchmark_rdtsc.bin
    munkresbenchmark_gprof.bin
    matrixgenerator.bin
)
