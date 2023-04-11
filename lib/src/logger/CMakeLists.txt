message("Build common library")

set(TARGET logger)
set(SOURCES
    logger.cpp
)
set(HEADER_DIR ${CMAKE_SOURCE_DIR}/lib/hdr/logger)

add_library(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PRIVATE ${HEADER_DIR})