# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/linux/myLinux/myWebServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/linux/myLinux/myWebServer/build

# Include any dependencies generated for this target.
include CMakeFiles/LiuServerPro.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LiuServerPro.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LiuServerPro.dir/flags.make

CMakeFiles/LiuServerPro.dir/main.cpp.o: CMakeFiles/LiuServerPro.dir/flags.make
CMakeFiles/LiuServerPro.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/linux/myLinux/myWebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LiuServerPro.dir/main.cpp.o"
	g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LiuServerPro.dir/main.cpp.o -c /root/linux/myLinux/myWebServer/main.cpp

CMakeFiles/LiuServerPro.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LiuServerPro.dir/main.cpp.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/linux/myLinux/myWebServer/main.cpp > CMakeFiles/LiuServerPro.dir/main.cpp.i

CMakeFiles/LiuServerPro.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LiuServerPro.dir/main.cpp.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/linux/myLinux/myWebServer/main.cpp -o CMakeFiles/LiuServerPro.dir/main.cpp.s

CMakeFiles/LiuServerPro.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/LiuServerPro.dir/main.cpp.o.requires

CMakeFiles/LiuServerPro.dir/main.cpp.o.provides: CMakeFiles/LiuServerPro.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/LiuServerPro.dir/build.make CMakeFiles/LiuServerPro.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/LiuServerPro.dir/main.cpp.o.provides

CMakeFiles/LiuServerPro.dir/main.cpp.o.provides.build: CMakeFiles/LiuServerPro.dir/main.cpp.o


# Object files for target LiuServerPro
LiuServerPro_OBJECTS = \
"CMakeFiles/LiuServerPro.dir/main.cpp.o"

# External object files for target LiuServerPro
LiuServerPro_EXTERNAL_OBJECTS =

LiuServerPro: CMakeFiles/LiuServerPro.dir/main.cpp.o
LiuServerPro: CMakeFiles/LiuServerPro.dir/build.make
LiuServerPro: ../lib/libNetlib.a
LiuServerPro: ../lib/libBaselib.a
LiuServerPro: ../lib/libTestlib.a
LiuServerPro: ../lib/libNetlib.a
LiuServerPro: ../lib/libBaselib.a
LiuServerPro: CMakeFiles/LiuServerPro.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/linux/myLinux/myWebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LiuServerPro"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LiuServerPro.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LiuServerPro.dir/build: LiuServerPro

.PHONY : CMakeFiles/LiuServerPro.dir/build

CMakeFiles/LiuServerPro.dir/requires: CMakeFiles/LiuServerPro.dir/main.cpp.o.requires

.PHONY : CMakeFiles/LiuServerPro.dir/requires

CMakeFiles/LiuServerPro.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LiuServerPro.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LiuServerPro.dir/clean

CMakeFiles/LiuServerPro.dir/depend:
	cd /root/linux/myLinux/myWebServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/linux/myLinux/myWebServer /root/linux/myLinux/myWebServer /root/linux/myLinux/myWebServer/build /root/linux/myLinux/myWebServer/build /root/linux/myLinux/myWebServer/build/CMakeFiles/LiuServerPro.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LiuServerPro.dir/depend

