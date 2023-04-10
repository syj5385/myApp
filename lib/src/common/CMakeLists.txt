message("Build common library")

set(TARGET common)
set(SOURCES
    logger.cpp
)
set(HEADER_DIR ${CMAKE_SOURCE_DIR}/lib/hdr/common)

add_library(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PRIVATE ${HEADER_DIR})