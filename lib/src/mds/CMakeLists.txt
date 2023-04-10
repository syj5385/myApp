message("Build common library")

set(TARGET mds)
set(SOURCES
    network.cpp
)
set(HEADER_DIR 
    ${CMAKE_SOURCE_DIR}/lib/hdr/mds
    ${CMAKE_SOURCE_DIR}/lib/hdr/common
)


add_library(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} PRIVATE common)
target_include_directories(${TARGET} PRIVATE ${HEADER_DIR})