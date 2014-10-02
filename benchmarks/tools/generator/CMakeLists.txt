# Data generator.
SET (MunkresCppMatrixGenerator_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/benchmarks/tools/generator)
ADD_EXECUTABLE (matrixgenerator.bin ${MunkresCppMatrixGenerator_SOURCES})
