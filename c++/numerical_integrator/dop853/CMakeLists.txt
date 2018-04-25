cmake_minimum_required(VERSION 3.7)
project(dop853)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp cmake-build-debug/CLRunner.cpp cmake-build-debug/CLRunner.h cmake-build-debug/Dopri853.cpp cmake-build-debug/Dopri853.h cmake-build-debug/constants.h cmake-build-debug/dop853.cpp cmake-build-debug/dop853.h)
add_executable(dop853 ${SOURCE_FILES})