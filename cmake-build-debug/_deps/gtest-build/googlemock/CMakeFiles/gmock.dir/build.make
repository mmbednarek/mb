# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /home/ego/apps/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/ego/apps/clion/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ego/projects/mb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ego/projects/mb/cmake-build-debug

# Include any dependencies generated for this target.
include _deps/gtest-build/googlemock/CMakeFiles/gmock.dir/depend.make

# Include the progress variables for this target.
include _deps/gtest-build/googlemock/CMakeFiles/gmock.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/gtest-build/googlemock/CMakeFiles/gmock.dir/flags.make

_deps/gtest-build/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o: _deps/gtest-build/googlemock/CMakeFiles/gmock.dir/flags.make
_deps/gtest-build/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o: _deps/gtest-src/googlemock/src/gmock-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ego/projects/mb/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/gtest-build/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o"
	cd /home/ego/projects/mb/cmake-build-debug/_deps/gtest-build/googlemock && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gmock.dir/src/gmock-all.cc.o -c /home/ego/projects/mb/cmake-build-debug/_deps/gtest-src/googlemock/src/gmock-all.cc

_deps/gtest-build/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock.dir/src/gmock-all.cc.i"
	cd /home/ego/projects/mb/cmake-build-debug/_deps/gtest-build/googlemock && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ego/projects/mb/cmake-build-debug/_deps/gtest-src/googlemock/src/gmock-all.cc > CMakeFiles/gmock.dir/src/gmock-all.cc.i

_deps/gtest-build/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock.dir/src/gmock-all.cc.s"
	cd /home/ego/projects/mb/cmake-build-debug/_deps/gtest-build/googlemock && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ego/projects/mb/cmake-build-debug/_deps/gtest-src/googlemock/src/gmock-all.cc -o CMakeFiles/gmock.dir/src/gmock-all.cc.s

# Object files for target gmock
gmock_OBJECTS = \
"CMakeFiles/gmock.dir/src/gmock-all.cc.o"

# External object files for target gmock
gmock_EXTERNAL_OBJECTS =

lib/libgmockd.a: _deps/gtest-build/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
lib/libgmockd.a: _deps/gtest-build/googlemock/CMakeFiles/gmock.dir/build.make
lib/libgmockd.a: _deps/gtest-build/googlemock/CMakeFiles/gmock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ego/projects/mb/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../lib/libgmockd.a"
	cd /home/ego/projects/mb/cmake-build-debug/_deps/gtest-build/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock.dir/cmake_clean_target.cmake
	cd /home/ego/projects/mb/cmake-build-debug/_deps/gtest-build/googlemock && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gmock.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/gtest-build/googlemock/CMakeFiles/gmock.dir/build: lib/libgmockd.a

.PHONY : _deps/gtest-build/googlemock/CMakeFiles/gmock.dir/build

_deps/gtest-build/googlemock/CMakeFiles/gmock.dir/clean:
	cd /home/ego/projects/mb/cmake-build-debug/_deps/gtest-build/googlemock && $(CMAKE_COMMAND) -P CMakeFiles/gmock.dir/cmake_clean.cmake
.PHONY : _deps/gtest-build/googlemock/CMakeFiles/gmock.dir/clean

_deps/gtest-build/googlemock/CMakeFiles/gmock.dir/depend:
	cd /home/ego/projects/mb/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ego/projects/mb /home/ego/projects/mb/cmake-build-debug/_deps/gtest-src/googlemock /home/ego/projects/mb/cmake-build-debug /home/ego/projects/mb/cmake-build-debug/_deps/gtest-build/googlemock /home/ego/projects/mb/cmake-build-debug/_deps/gtest-build/googlemock/CMakeFiles/gmock.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/gtest-build/googlemock/CMakeFiles/gmock.dir/depend

