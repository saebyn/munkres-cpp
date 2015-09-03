# Common variable.
include_directories (${PROJECT_SOURCE_DIR}/benchmarks/tools/generator)


# Benchmark based on the Google benchmark Framework.
find_package (GoogleBenchmark)
if    (GBENCHMARK_FOUND)
    set (MunkresCppBenchmarkGoogle_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_google.cpp)
    add_executable (munkresbenchmark_google.bin ${MunkresCppBenchmarkGoogle_SOURCES})
    include_directories (${GBENCHMARK_INCLUDE_DIR})
    target_link_libraries (munkresbenchmark_google.bin munkres ${GBENCHMARK_LIBRARY} pthread)
endif (GBENCHMARK_FOUND)


# Benchmark based on the hayai Framework.
find_package (HayaiBenchmark REQUIRED)
if    (HAYAI_FOUND)
    set (MunkresCppBenchmarkHayai_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_hayai.cpp)
    add_executable (munkresbenchmark_hayai.bin ${MunkresCppBenchmarkHayai_SOURCES})
    include_directories (${HAYAI_INCLUDE_DIR})
    target_link_libraries (munkresbenchmark_hayai.bin munkres)
endif (HAYAI_FOUND)


# Benchmark based on the Celero Framework.
find_package (CeleroBenchmark REQUIRED)
if    (CELERO_FOUND)
    set (MunkresCppBenchmarkCelero_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_celero.cpp)
    add_executable (munkresbenchmark_celero.bin ${MunkresCppBenchmarkCelero_SOURCES})
    include_directories (${CELERO_INCLUDE_DIR})
    target_link_libraries (munkresbenchmark_celero.bin munkres ${CELERO_LIBRARY})
endif (CELERO_FOUND)


# Benchmark based on the RDTSC.
set (MunkresCppBenchmarkRdtsc_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_rdtsc.cpp)
add_executable (munkresbenchmark_rdtsc.bin ${MunkresCppBenchmarkRdtsc_SOURCES})
target_link_libraries (munkresbenchmark_rdtsc.bin munkres)


# Test for generate profiler (gprof) data.
set (MunkresCppBenchmarkGprof_SOURCES
    ${PROJECT_SOURCE_DIR}/src/munkres.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main_gprof.cpp
)
add_executable (munkresbenchmark_gprof.bin ${MunkresCppBenchmarkGprof_SOURCES})
set_target_properties (munkresbenchmark_gprof.bin PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -pg" LINK_FLAGS "-pg")


# Prevent launch tests before will be generated test data set.
set (BenchmarkDataSet ${PROJECT_BINARY_DIR}/matrices.txt)
add_custom_command (
    OUTPUT ${BenchmarkDataSet}
    COMMAND cd ${PROJECT_BINARY_DIR} && ./benchmarks/tools/generator/matrixgenerator.bin 20
)
add_custom_target (generate_benchmark_dataset DEPENDS ${BenchmarkDataSet})

add_dependencies (munkresbenchmark_google.bin generate_benchmark_dataset)
add_dependencies (munkresbenchmark_hayai.bin  generate_benchmark_dataset)
add_dependencies (munkresbenchmark_celero.bin generate_benchmark_dataset)
add_dependencies (munkresbenchmark_rdtsc.bin  generate_benchmark_dataset)
add_dependencies (munkresbenchmark_gprof.bin  generate_benchmark_dataset)
