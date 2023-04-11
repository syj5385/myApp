message("Build common library")

set(TARGET common)
set(SOURCES
    cli.cpp
)
set(HEADER_DIR 
    ${CMAKE_SOURCE_DIR}/lib/hdr/common
    ${CMAKE_SOURCE_DIR}/lib/hdr/logger
)

add_library(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} logger)
target_include_directories(${TARGET} PRIVATE ${HEADER_DIR})