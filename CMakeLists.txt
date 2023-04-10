cmake_minimum_required(VERSION 3.0.1)
project(myApp)

add_compile_options(-std=c++11)

add_subdirectory(lib)
add_subdirectory(src)