# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/ernesto/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.4445.84/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/ernesto/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.4445.84/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ernesto/Desktop/workspace/c++/opengl/starter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ernesto/Desktop/workspace/c++/opengl/starter/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/starter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/starter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/starter.dir/flags.make

CMakeFiles/starter.dir/main.cpp.o: CMakeFiles/starter.dir/flags.make
CMakeFiles/starter.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ernesto/Desktop/workspace/c++/opengl/starter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/starter.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/starter.dir/main.cpp.o -c /home/ernesto/Desktop/workspace/c++/opengl/starter/main.cpp

CMakeFiles/starter.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/starter.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ernesto/Desktop/workspace/c++/opengl/starter/main.cpp > CMakeFiles/starter.dir/main.cpp.i

CMakeFiles/starter.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/starter.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ernesto/Desktop/workspace/c++/opengl/starter/main.cpp -o CMakeFiles/starter.dir/main.cpp.s

CMakeFiles/starter.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/starter.dir/main.cpp.o.requires

CMakeFiles/starter.dir/main.cpp.o.provides: CMakeFiles/starter.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/starter.dir/build.make CMakeFiles/starter.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/starter.dir/main.cpp.o.provides

CMakeFiles/starter.dir/main.cpp.o.provides.build: CMakeFiles/starter.dir/main.cpp.o


CMakeFiles/starter.dir/VertexBuffer.cpp.o: CMakeFiles/starter.dir/flags.make
CMakeFiles/starter.dir/VertexBuffer.cpp.o: ../VertexBuffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ernesto/Desktop/workspace/c++/opengl/starter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/starter.dir/VertexBuffer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/starter.dir/VertexBuffer.cpp.o -c /home/ernesto/Desktop/workspace/c++/opengl/starter/VertexBuffer.cpp

CMakeFiles/starter.dir/VertexBuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/starter.dir/VertexBuffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ernesto/Desktop/workspace/c++/opengl/starter/VertexBuffer.cpp > CMakeFiles/starter.dir/VertexBuffer.cpp.i

CMakeFiles/starter.dir/VertexBuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/starter.dir/VertexBuffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ernesto/Desktop/workspace/c++/opengl/starter/VertexBuffer.cpp -o CMakeFiles/starter.dir/VertexBuffer.cpp.s

CMakeFiles/starter.dir/VertexBuffer.cpp.o.requires:

.PHONY : CMakeFiles/starter.dir/VertexBuffer.cpp.o.requires

CMakeFiles/starter.dir/VertexBuffer.cpp.o.provides: CMakeFiles/starter.dir/VertexBuffer.cpp.o.requires
	$(MAKE) -f CMakeFiles/starter.dir/build.make CMakeFiles/starter.dir/VertexBuffer.cpp.o.provides.build
.PHONY : CMakeFiles/starter.dir/VertexBuffer.cpp.o.provides

CMakeFiles/starter.dir/VertexBuffer.cpp.o.provides.build: CMakeFiles/starter.dir/VertexBuffer.cpp.o


CMakeFiles/starter.dir/ShaderProgram.cpp.o: CMakeFiles/starter.dir/flags.make
CMakeFiles/starter.dir/ShaderProgram.cpp.o: ShaderProgram.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ernesto/Desktop/workspace/c++/opengl/starter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/starter.dir/ShaderProgram.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/starter.dir/ShaderProgram.cpp.o -c /home/ernesto/Desktop/workspace/c++/opengl/starter/cmake-build-debug/ShaderProgram.cpp

CMakeFiles/starter.dir/ShaderProgram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/starter.dir/ShaderProgram.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ernesto/Desktop/workspace/c++/opengl/starter/cmake-build-debug/ShaderProgram.cpp > CMakeFiles/starter.dir/ShaderProgram.cpp.i

CMakeFiles/starter.dir/ShaderProgram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/starter.dir/ShaderProgram.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ernesto/Desktop/workspace/c++/opengl/starter/cmake-build-debug/ShaderProgram.cpp -o CMakeFiles/starter.dir/ShaderProgram.cpp.s

CMakeFiles/starter.dir/ShaderProgram.cpp.o.requires:

.PHONY : CMakeFiles/starter.dir/ShaderProgram.cpp.o.requires

CMakeFiles/starter.dir/ShaderProgram.cpp.o.provides: CMakeFiles/starter.dir/ShaderProgram.cpp.o.requires
	$(MAKE) -f CMakeFiles/starter.dir/build.make CMakeFiles/starter.dir/ShaderProgram.cpp.o.provides.build
.PHONY : CMakeFiles/starter.dir/ShaderProgram.cpp.o.provides

CMakeFiles/starter.dir/ShaderProgram.cpp.o.provides.build: CMakeFiles/starter.dir/ShaderProgram.cpp.o


# Object files for target starter
starter_OBJECTS = \
"CMakeFiles/starter.dir/main.cpp.o" \
"CMakeFiles/starter.dir/VertexBuffer.cpp.o" \
"CMakeFiles/starter.dir/ShaderProgram.cpp.o"

# External object files for target starter
starter_EXTERNAL_OBJECTS =

starter: CMakeFiles/starter.dir/main.cpp.o
starter: CMakeFiles/starter.dir/VertexBuffer.cpp.o
starter: CMakeFiles/starter.dir/ShaderProgram.cpp.o
starter: CMakeFiles/starter.dir/build.make
starter: /usr/lib/libGL.so
starter: /usr/lib/libGLEW.so
starter: CMakeFiles/starter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ernesto/Desktop/workspace/c++/opengl/starter/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable starter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/starter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/starter.dir/build: starter

.PHONY : CMakeFiles/starter.dir/build

CMakeFiles/starter.dir/requires: CMakeFiles/starter.dir/main.cpp.o.requires
CMakeFiles/starter.dir/requires: CMakeFiles/starter.dir/VertexBuffer.cpp.o.requires
CMakeFiles/starter.dir/requires: CMakeFiles/starter.dir/ShaderProgram.cpp.o.requires

.PHONY : CMakeFiles/starter.dir/requires

CMakeFiles/starter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/starter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/starter.dir/clean

CMakeFiles/starter.dir/depend:
	cd /home/ernesto/Desktop/workspace/c++/opengl/starter/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ernesto/Desktop/workspace/c++/opengl/starter /home/ernesto/Desktop/workspace/c++/opengl/starter /home/ernesto/Desktop/workspace/c++/opengl/starter/cmake-build-debug /home/ernesto/Desktop/workspace/c++/opengl/starter/cmake-build-debug /home/ernesto/Desktop/workspace/c++/opengl/starter/cmake-build-debug/CMakeFiles/starter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/starter.dir/depend

