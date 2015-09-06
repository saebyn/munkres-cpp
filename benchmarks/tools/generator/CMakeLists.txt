# Data generator.
set (MunkresCppMatrixGenerator_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
include_directories (${PROJECT_SOURCE_DIR}/benchmarks/tools/generator)
add_executable (matrixgenerator.bin EXCLUDE_FROM_ALL ${MunkresCppMatrixGenerator_SOURCES})
