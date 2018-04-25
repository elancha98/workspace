cmake_minimum_required(VERSION 3.10)
project(starter)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(starter main.cpp VertexBuffer.cpp VertexBuffer.h cmake-build-debug/ShaderProgram.cpp cmake-build-debug/ShaderProgram.h)

target_include_directories(starter PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(starter PUBLIC ${GLFW_INCLUDE_DIRS})
target_include_directories(starter PUBLIC ${GLEW_INCLUDE_DIRS})

target_link_libraries(starter ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})