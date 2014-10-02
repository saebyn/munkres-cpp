# Common variable.
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/benchmarks/tools/generator)


# Benchmark based on the Google benchmark Framework.
find_package (GoogleBenchmark)
if    (GBENCHMARK_FOUND)
    SET (MunkresCppBenchmarkGoogle_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_google.cpp)
    ADD_EXECUTABLE (munkresbenchmark_google.bin ${MunkresCppBenchmarkGoogle_SOURCES})
    INCLUDE_DIRECTORIES (${GBENCHMARK_INCLUDE_DIR})
    TARGET_LINK_LIBRARIES (munkresbenchmark_google.bin munkres ${GBENCHMARK_LIBRARY} pthread)
endif (GBENCHMARK_FOUND)


# Benchmark based on the hayai Framework.
find_package (HayaiBenchmark REQUIRED)
if    (HAYAI_FOUND)
    SET (MunkresCppBenchmarkHayai_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_hayai.cpp)
    ADD_EXECUTABLE (munkresbenchmark_hayai.bin ${MunkresCppBenchmarkHayai_SOURCES})
    INCLUDE_DIRECTORIES (${HAYAI_INCLUDE_DIR})
    TARGET_LINK_LIBRARIES (munkresbenchmark_hayai.bin munkres)
endif (HAYAI_FOUND)


# Benchmark based on the Celero Framework.
find_package (CeleroBenchmark REQUIRED)
if    (CELERO_FOUND)
    SET (MunkresCppBenchmarkCelero_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_celero.cpp)
    ADD_EXECUTABLE (munkresbenchmark_celero.bin ${MunkresCppBenchmarkCelero_SOURCES})
    INCLUDE_DIRECTORIES (${CELERO_INCLUDE_DIR})
    TARGET_LINK_LIBRARIES (munkresbenchmark_celero.bin munkres ${CELERO_LIBRARY})
endif (CELERO_FOUND)


# Benchmark based on the RDTSC.
SET (MunkresCppBenchmarkRdtsc_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_rdtsc.cpp)
ADD_EXECUTABLE (munkresbenchmark_rdtsc.bin ${MunkresCppBenchmarkRdtsc_SOURCES})
TARGET_LINK_LIBRARIES (munkresbenchmark_rdtsc.bin munkres)
