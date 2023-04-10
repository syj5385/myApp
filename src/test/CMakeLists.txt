message("Build test directory")

message("Include DIR: ${CMAKE_SOURCE_DIR}/lib/hdr/common")

include_directories(include ${CMAKE_SOURCE_DIR}/lib/hdr/common)
link_libraries(common)

add_executable(test_network test_network.cpp)
target_include_directories(test_network PRIVATE ${CMAKE_SOURCE_DIR}/lib/hdr/mds)
target_link_libraries(test_network PRIVATE mds pthread)
