message("Build test directory")

message("Include DIR: ${CMAKE_SOURCE_DIR}/lib/hdr/common")

include_directories(include 
    ${CMAKE_SOURCE_DIR}/lib/hdr/common
    ${CMAKE_SOURCE_DIR}/lib/hdr/logger
)
link_libraries(cli logger)

add_executable(test_network test_network.cpp)
target_include_directories(test_network PRIVATE ${CMAKE_SOURCE_DIR}/lib/hdr/mds)
target_link_libraries(test_network PRIVATE mds pthread)

add_executable(test_cli test_cli.cpp)
target_include_directories(test_cli PRIVATE ${CMAKE_SOURCE_DIR}/lib/hdr/cli)
target_link_libraries(test_network PRIVATE pthread)
