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
include LiuServer/base/CMakeFiles/Baselib.dir/depend.make

# Include the progress variables for this target.
include LiuServer/base/CMakeFiles/Baselib.dir/progress.make

# Include the compile flags for this target's objects.
include LiuServer/base/CMakeFiles/Baselib.dir/flags.make

LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.o: LiuServer/base/CMakeFiles/Baselib.dir/flags.make
LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.o: ../LiuServer/base/AsyncLogging.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/linux/myLinux/myWebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.o"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Baselib.dir/AsyncLogging.cpp.o -c /root/linux/myLinux/myWebServer/LiuServer/base/AsyncLogging.cpp

LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Baselib.dir/AsyncLogging.cpp.i"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/linux/myLinux/myWebServer/LiuServer/base/AsyncLogging.cpp > CMakeFiles/Baselib.dir/AsyncLogging.cpp.i

LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Baselib.dir/AsyncLogging.cpp.s"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/linux/myLinux/myWebServer/LiuServer/base/AsyncLogging.cpp -o CMakeFiles/Baselib.dir/AsyncLogging.cpp.s

LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.o.requires:

.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.o.requires

LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.o.provides: LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.o.requires
	$(MAKE) -f LiuServer/base/CMakeFiles/Baselib.dir/build.make LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.o.provides.build
.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.o.provides

LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.o.provides.build: LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.o


LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.o: LiuServer/base/CMakeFiles/Baselib.dir/flags.make
LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.o: ../LiuServer/base/CountDownLatch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/linux/myLinux/myWebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.o"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Baselib.dir/CountDownLatch.cpp.o -c /root/linux/myLinux/myWebServer/LiuServer/base/CountDownLatch.cpp

LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Baselib.dir/CountDownLatch.cpp.i"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/linux/myLinux/myWebServer/LiuServer/base/CountDownLatch.cpp > CMakeFiles/Baselib.dir/CountDownLatch.cpp.i

LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Baselib.dir/CountDownLatch.cpp.s"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/linux/myLinux/myWebServer/LiuServer/base/CountDownLatch.cpp -o CMakeFiles/Baselib.dir/CountDownLatch.cpp.s

LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.o.requires:

.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.o.requires

LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.o.provides: LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.o.requires
	$(MAKE) -f LiuServer/base/CMakeFiles/Baselib.dir/build.make LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.o.provides.build
.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.o.provides

LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.o.provides.build: LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.o


LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.o: LiuServer/base/CMakeFiles/Baselib.dir/flags.make
LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.o: ../LiuServer/base/FileUtil.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/linux/myLinux/myWebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.o"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Baselib.dir/FileUtil.cpp.o -c /root/linux/myLinux/myWebServer/LiuServer/base/FileUtil.cpp

LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Baselib.dir/FileUtil.cpp.i"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/linux/myLinux/myWebServer/LiuServer/base/FileUtil.cpp > CMakeFiles/Baselib.dir/FileUtil.cpp.i

LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Baselib.dir/FileUtil.cpp.s"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/linux/myLinux/myWebServer/LiuServer/base/FileUtil.cpp -o CMakeFiles/Baselib.dir/FileUtil.cpp.s

LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.o.requires:

.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.o.requires

LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.o.provides: LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.o.requires
	$(MAKE) -f LiuServer/base/CMakeFiles/Baselib.dir/build.make LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.o.provides.build
.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.o.provides

LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.o.provides.build: LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.o


LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.o: LiuServer/base/CMakeFiles/Baselib.dir/flags.make
LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.o: ../LiuServer/base/LogFile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/linux/myLinux/myWebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.o"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Baselib.dir/LogFile.cpp.o -c /root/linux/myLinux/myWebServer/LiuServer/base/LogFile.cpp

LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Baselib.dir/LogFile.cpp.i"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/linux/myLinux/myWebServer/LiuServer/base/LogFile.cpp > CMakeFiles/Baselib.dir/LogFile.cpp.i

LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Baselib.dir/LogFile.cpp.s"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/linux/myLinux/myWebServer/LiuServer/base/LogFile.cpp -o CMakeFiles/Baselib.dir/LogFile.cpp.s

LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.o.requires:

.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.o.requires

LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.o.provides: LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.o.requires
	$(MAKE) -f LiuServer/base/CMakeFiles/Baselib.dir/build.make LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.o.provides.build
.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.o.provides

LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.o.provides.build: LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.o


LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.o: LiuServer/base/CMakeFiles/Baselib.dir/flags.make
LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.o: ../LiuServer/base/LogStream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/linux/myLinux/myWebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.o"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Baselib.dir/LogStream.cpp.o -c /root/linux/myLinux/myWebServer/LiuServer/base/LogStream.cpp

LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Baselib.dir/LogStream.cpp.i"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/linux/myLinux/myWebServer/LiuServer/base/LogStream.cpp > CMakeFiles/Baselib.dir/LogStream.cpp.i

LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Baselib.dir/LogStream.cpp.s"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/linux/myLinux/myWebServer/LiuServer/base/LogStream.cpp -o CMakeFiles/Baselib.dir/LogStream.cpp.s

LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.o.requires:

.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.o.requires

LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.o.provides: LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.o.requires
	$(MAKE) -f LiuServer/base/CMakeFiles/Baselib.dir/build.make LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.o.provides.build
.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.o.provides

LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.o.provides.build: LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.o


LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.o: LiuServer/base/CMakeFiles/Baselib.dir/flags.make
LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.o: ../LiuServer/base/Logging.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/linux/myLinux/myWebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.o"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Baselib.dir/Logging.cpp.o -c /root/linux/myLinux/myWebServer/LiuServer/base/Logging.cpp

LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Baselib.dir/Logging.cpp.i"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/linux/myLinux/myWebServer/LiuServer/base/Logging.cpp > CMakeFiles/Baselib.dir/Logging.cpp.i

LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Baselib.dir/Logging.cpp.s"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/linux/myLinux/myWebServer/LiuServer/base/Logging.cpp -o CMakeFiles/Baselib.dir/Logging.cpp.s

LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.o.requires:

.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.o.requires

LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.o.provides: LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.o.requires
	$(MAKE) -f LiuServer/base/CMakeFiles/Baselib.dir/build.make LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.o.provides.build
.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.o.provides

LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.o.provides.build: LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.o


LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.o: LiuServer/base/CMakeFiles/Baselib.dir/flags.make
LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.o: ../LiuServer/base/MyDB.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/linux/myLinux/myWebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.o"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Baselib.dir/MyDB.cpp.o -c /root/linux/myLinux/myWebServer/LiuServer/base/MyDB.cpp

LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Baselib.dir/MyDB.cpp.i"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/linux/myLinux/myWebServer/LiuServer/base/MyDB.cpp > CMakeFiles/Baselib.dir/MyDB.cpp.i

LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Baselib.dir/MyDB.cpp.s"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/linux/myLinux/myWebServer/LiuServer/base/MyDB.cpp -o CMakeFiles/Baselib.dir/MyDB.cpp.s

LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.o.requires:

.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.o.requires

LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.o.provides: LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.o.requires
	$(MAKE) -f LiuServer/base/CMakeFiles/Baselib.dir/build.make LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.o.provides.build
.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.o.provides

LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.o.provides.build: LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.o


LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.o: LiuServer/base/CMakeFiles/Baselib.dir/flags.make
LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.o: ../LiuServer/base/Thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/linux/myLinux/myWebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.o"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Baselib.dir/Thread.cpp.o -c /root/linux/myLinux/myWebServer/LiuServer/base/Thread.cpp

LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Baselib.dir/Thread.cpp.i"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/linux/myLinux/myWebServer/LiuServer/base/Thread.cpp > CMakeFiles/Baselib.dir/Thread.cpp.i

LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Baselib.dir/Thread.cpp.s"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/linux/myLinux/myWebServer/LiuServer/base/Thread.cpp -o CMakeFiles/Baselib.dir/Thread.cpp.s

LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.o.requires:

.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.o.requires

LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.o.provides: LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.o.requires
	$(MAKE) -f LiuServer/base/CMakeFiles/Baselib.dir/build.make LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.o.provides.build
.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.o.provides

LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.o.provides.build: LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.o


LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.o: LiuServer/base/CMakeFiles/Baselib.dir/flags.make
LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.o: ../LiuServer/base/ThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/linux/myLinux/myWebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.o"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Baselib.dir/ThreadPool.cpp.o -c /root/linux/myLinux/myWebServer/LiuServer/base/ThreadPool.cpp

LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Baselib.dir/ThreadPool.cpp.i"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/linux/myLinux/myWebServer/LiuServer/base/ThreadPool.cpp > CMakeFiles/Baselib.dir/ThreadPool.cpp.i

LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Baselib.dir/ThreadPool.cpp.s"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/linux/myLinux/myWebServer/LiuServer/base/ThreadPool.cpp -o CMakeFiles/Baselib.dir/ThreadPool.cpp.s

LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.o.requires:

.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.o.requires

LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.o.provides: LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.o.requires
	$(MAKE) -f LiuServer/base/CMakeFiles/Baselib.dir/build.make LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.o.provides.build
.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.o.provides

LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.o.provides.build: LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.o


LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.o: LiuServer/base/CMakeFiles/Baselib.dir/flags.make
LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.o: ../LiuServer/base/Timestamp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/linux/myLinux/myWebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.o"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Baselib.dir/Timestamp.cpp.o -c /root/linux/myLinux/myWebServer/LiuServer/base/Timestamp.cpp

LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Baselib.dir/Timestamp.cpp.i"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/linux/myLinux/myWebServer/LiuServer/base/Timestamp.cpp > CMakeFiles/Baselib.dir/Timestamp.cpp.i

LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Baselib.dir/Timestamp.cpp.s"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/linux/myLinux/myWebServer/LiuServer/base/Timestamp.cpp -o CMakeFiles/Baselib.dir/Timestamp.cpp.s

LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.o.requires:

.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.o.requires

LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.o.provides: LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.o.requires
	$(MAKE) -f LiuServer/base/CMakeFiles/Baselib.dir/build.make LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.o.provides.build
.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.o.provides

LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.o.provides.build: LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.o


# Object files for target Baselib
Baselib_OBJECTS = \
"CMakeFiles/Baselib.dir/AsyncLogging.cpp.o" \
"CMakeFiles/Baselib.dir/CountDownLatch.cpp.o" \
"CMakeFiles/Baselib.dir/FileUtil.cpp.o" \
"CMakeFiles/Baselib.dir/LogFile.cpp.o" \
"CMakeFiles/Baselib.dir/LogStream.cpp.o" \
"CMakeFiles/Baselib.dir/Logging.cpp.o" \
"CMakeFiles/Baselib.dir/MyDB.cpp.o" \
"CMakeFiles/Baselib.dir/Thread.cpp.o" \
"CMakeFiles/Baselib.dir/ThreadPool.cpp.o" \
"CMakeFiles/Baselib.dir/Timestamp.cpp.o"

# External object files for target Baselib
Baselib_EXTERNAL_OBJECTS =

../lib/libBaselib.a: LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.o
../lib/libBaselib.a: LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.o
../lib/libBaselib.a: LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.o
../lib/libBaselib.a: LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.o
../lib/libBaselib.a: LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.o
../lib/libBaselib.a: LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.o
../lib/libBaselib.a: LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.o
../lib/libBaselib.a: LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.o
../lib/libBaselib.a: LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.o
../lib/libBaselib.a: LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.o
../lib/libBaselib.a: LiuServer/base/CMakeFiles/Baselib.dir/build.make
../lib/libBaselib.a: LiuServer/base/CMakeFiles/Baselib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/linux/myLinux/myWebServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX static library ../../../lib/libBaselib.a"
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && $(CMAKE_COMMAND) -P CMakeFiles/Baselib.dir/cmake_clean_target.cmake
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Baselib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
LiuServer/base/CMakeFiles/Baselib.dir/build: ../lib/libBaselib.a

.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/build

LiuServer/base/CMakeFiles/Baselib.dir/requires: LiuServer/base/CMakeFiles/Baselib.dir/AsyncLogging.cpp.o.requires
LiuServer/base/CMakeFiles/Baselib.dir/requires: LiuServer/base/CMakeFiles/Baselib.dir/CountDownLatch.cpp.o.requires
LiuServer/base/CMakeFiles/Baselib.dir/requires: LiuServer/base/CMakeFiles/Baselib.dir/FileUtil.cpp.o.requires
LiuServer/base/CMakeFiles/Baselib.dir/requires: LiuServer/base/CMakeFiles/Baselib.dir/LogFile.cpp.o.requires
LiuServer/base/CMakeFiles/Baselib.dir/requires: LiuServer/base/CMakeFiles/Baselib.dir/LogStream.cpp.o.requires
LiuServer/base/CMakeFiles/Baselib.dir/requires: LiuServer/base/CMakeFiles/Baselib.dir/Logging.cpp.o.requires
LiuServer/base/CMakeFiles/Baselib.dir/requires: LiuServer/base/CMakeFiles/Baselib.dir/MyDB.cpp.o.requires
LiuServer/base/CMakeFiles/Baselib.dir/requires: LiuServer/base/CMakeFiles/Baselib.dir/Thread.cpp.o.requires
LiuServer/base/CMakeFiles/Baselib.dir/requires: LiuServer/base/CMakeFiles/Baselib.dir/ThreadPool.cpp.o.requires
LiuServer/base/CMakeFiles/Baselib.dir/requires: LiuServer/base/CMakeFiles/Baselib.dir/Timestamp.cpp.o.requires

.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/requires

LiuServer/base/CMakeFiles/Baselib.dir/clean:
	cd /root/linux/myLinux/myWebServer/build/LiuServer/base && $(CMAKE_COMMAND) -P CMakeFiles/Baselib.dir/cmake_clean.cmake
.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/clean

LiuServer/base/CMakeFiles/Baselib.dir/depend:
	cd /root/linux/myLinux/myWebServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/linux/myLinux/myWebServer /root/linux/myLinux/myWebServer/LiuServer/base /root/linux/myLinux/myWebServer/build /root/linux/myLinux/myWebServer/build/LiuServer/base /root/linux/myLinux/myWebServer/build/LiuServer/base/CMakeFiles/Baselib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : LiuServer/base/CMakeFiles/Baselib.dir/depend

