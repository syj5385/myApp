message("Build common library")

set(TARGET mds)
set(SOURCES
    network.cpp
)

include_directories(include 
    ${CMAKE_SOURCE_DIR}/lib/hdr/common
    ${CMAKE_SOURCE_DIR}/lib/hdr/logger
)
link_libraries(logger)

set(HEADER_DIR 
    ${CMAKE_SOURCE_DIR}/lib/hdr/mds
)

add_library(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PRIVATE ${HEADER_DIR})
# target_link_libraries(${TARGET} PRIVATE common)
