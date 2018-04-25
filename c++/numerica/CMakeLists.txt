cmake_minimum_required(VERSION 3.7)
project(numerica)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Matrix.cc Matrix.hh Utils.hh matrices.cc)
add_executable(numerica ${SOURCE_FILES})