message("Build cli library")

set(TARGET cli)
set(SOURCES
    cli.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/lib/hdr/common)

set(HEADER_DIR 
    ${CMAKE_SOURCE_DIR}/lib/hdr/cli
    ${CMAKE_SOURCE_DIR}/lib/hdr/logger
    ${CMAKE_SOURCE_DIR}/lib/hdr/mds
)

set(LIBRARIES
    logger
    mds
)
add_library(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} ${LIBRARIES})
target_include_directories(${TARGET} PRIVATE ${HEADER_DIR})