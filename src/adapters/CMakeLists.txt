set (
    MunkresAdapters_HEADERS
    ${PROJECT_SOURCE_DIR}/src/adapters/adapter.h
    )

set (
    MunkresCppLib_SOURCES
    ${MunkresCppLib_SOURCES}
    ${PROJECT_SOURCE_DIR}/src/adapters/adapter.cpp
    )

option(STD_ADAPTERS "Build 2D array, std::array and std::vector adapters" OFF)
if(STD_ADAPTERS)
    set (MunkresCppLib_HEADERS
    ${MunkresCppLib_HEADERS}
    ${PROJECT_SOURCE_DIR}/src/adapters/std2dvectoradapter.h
    ${PROJECT_SOURCE_DIR}/src/adapters/std2darrayadapter.h
    )

    set (
    MunkresCppLib_SOURCES
    ${MunkresCppLib_SOURCES}
    ${PROJECT_SOURCE_DIR}/src/adapters/std2dvectordapter.cpp
    ${PROJECT_SOURCE_DIR}/src/adapters/std2darrayadapter.cpp
    )
endif(STD_ADAPTERS)

option(BOOST_MATRIX_ADAPTER "Build boost::numeric::ublas::matrix adapter" OFF)
if(BOOST_MATRIX_ADAPTER)
    find_package (Boost REQUIRED)
    set (MunkresCppLib_HEADERS ${MunkresCppLib_HEADERS}
    ${PROJECT_SOURCE_DIR}/src/adapters/boostmatrixadapter.h
    )
    
    set (
    MunkresCppLib_SOURCES
    ${MunkresCppLib_SOURCES}
    ${PROJECT_SOURCE_DIR}/src/adapters/boostmatrixadapter.cpp
    )
endif(BOOST_MATRIX_ADAPTER)

#propagate upward edited sources
set(MunkresCppLib_SOURCES ${MunkresCppLib_SOURCES} PARENT_SCOPE)

#install all selected adapters
install (FILES ${MunkresAdapters_HEADERS}  DESTINATION include/munkres/adapters PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)

