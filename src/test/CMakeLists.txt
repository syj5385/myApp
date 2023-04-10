message("Build test directory")

message("Include DIR: ${CMAKE_SOURCE_DIR}/lib/hdr/common")

include_directories(include ${CMAKE_SOURCE_DIR}/lib/hdr/common)
link_libraries(common)

add_executable(test_log test_log.cpp)
