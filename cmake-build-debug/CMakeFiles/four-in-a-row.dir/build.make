# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /cygdrive/c/Users/renda/.CLion2017.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/renda/.CLion2017.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/four-in-a-row.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/four-in-a-row.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/four-in-a-row.dir/flags.make

CMakeFiles/four-in-a-row.dir/main.cpp.o: CMakeFiles/four-in-a-row.dir/flags.make
CMakeFiles/four-in-a-row.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/four-in-a-row.dir/main.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/four-in-a-row.dir/main.cpp.o -c /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/main.cpp

CMakeFiles/four-in-a-row.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/four-in-a-row.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/main.cpp > CMakeFiles/four-in-a-row.dir/main.cpp.i

CMakeFiles/four-in-a-row.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/four-in-a-row.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/main.cpp -o CMakeFiles/four-in-a-row.dir/main.cpp.s

CMakeFiles/four-in-a-row.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/four-in-a-row.dir/main.cpp.o.requires

CMakeFiles/four-in-a-row.dir/main.cpp.o.provides: CMakeFiles/four-in-a-row.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/four-in-a-row.dir/build.make CMakeFiles/four-in-a-row.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/four-in-a-row.dir/main.cpp.o.provides

CMakeFiles/four-in-a-row.dir/main.cpp.o.provides.build: CMakeFiles/four-in-a-row.dir/main.cpp.o


CMakeFiles/four-in-a-row.dir/c4.cpp.o: CMakeFiles/four-in-a-row.dir/flags.make
CMakeFiles/four-in-a-row.dir/c4.cpp.o: ../c4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/four-in-a-row.dir/c4.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/four-in-a-row.dir/c4.cpp.o -c /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/c4.cpp

CMakeFiles/four-in-a-row.dir/c4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/four-in-a-row.dir/c4.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/c4.cpp > CMakeFiles/four-in-a-row.dir/c4.cpp.i

CMakeFiles/four-in-a-row.dir/c4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/four-in-a-row.dir/c4.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/c4.cpp -o CMakeFiles/four-in-a-row.dir/c4.cpp.s

CMakeFiles/four-in-a-row.dir/c4.cpp.o.requires:

.PHONY : CMakeFiles/four-in-a-row.dir/c4.cpp.o.requires

CMakeFiles/four-in-a-row.dir/c4.cpp.o.provides: CMakeFiles/four-in-a-row.dir/c4.cpp.o.requires
	$(MAKE) -f CMakeFiles/four-in-a-row.dir/build.make CMakeFiles/four-in-a-row.dir/c4.cpp.o.provides.build
.PHONY : CMakeFiles/four-in-a-row.dir/c4.cpp.o.provides

CMakeFiles/four-in-a-row.dir/c4.cpp.o.provides.build: CMakeFiles/four-in-a-row.dir/c4.cpp.o


CMakeFiles/four-in-a-row.dir/c4bot.cpp.o: CMakeFiles/four-in-a-row.dir/flags.make
CMakeFiles/four-in-a-row.dir/c4bot.cpp.o: ../c4bot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/four-in-a-row.dir/c4bot.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/four-in-a-row.dir/c4bot.cpp.o -c /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/c4bot.cpp

CMakeFiles/four-in-a-row.dir/c4bot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/four-in-a-row.dir/c4bot.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/c4bot.cpp > CMakeFiles/four-in-a-row.dir/c4bot.cpp.i

CMakeFiles/four-in-a-row.dir/c4bot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/four-in-a-row.dir/c4bot.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/c4bot.cpp -o CMakeFiles/four-in-a-row.dir/c4bot.cpp.s

CMakeFiles/four-in-a-row.dir/c4bot.cpp.o.requires:

.PHONY : CMakeFiles/four-in-a-row.dir/c4bot.cpp.o.requires

CMakeFiles/four-in-a-row.dir/c4bot.cpp.o.provides: CMakeFiles/four-in-a-row.dir/c4bot.cpp.o.requires
	$(MAKE) -f CMakeFiles/four-in-a-row.dir/build.make CMakeFiles/four-in-a-row.dir/c4bot.cpp.o.provides.build
.PHONY : CMakeFiles/four-in-a-row.dir/c4bot.cpp.o.provides

CMakeFiles/four-in-a-row.dir/c4bot.cpp.o.provides.build: CMakeFiles/four-in-a-row.dir/c4bot.cpp.o


CMakeFiles/four-in-a-row.dir/node.cpp.o: CMakeFiles/four-in-a-row.dir/flags.make
CMakeFiles/four-in-a-row.dir/node.cpp.o: ../node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/four-in-a-row.dir/node.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/four-in-a-row.dir/node.cpp.o -c /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/node.cpp

CMakeFiles/four-in-a-row.dir/node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/four-in-a-row.dir/node.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/node.cpp > CMakeFiles/four-in-a-row.dir/node.cpp.i

CMakeFiles/four-in-a-row.dir/node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/four-in-a-row.dir/node.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/node.cpp -o CMakeFiles/four-in-a-row.dir/node.cpp.s

CMakeFiles/four-in-a-row.dir/node.cpp.o.requires:

.PHONY : CMakeFiles/four-in-a-row.dir/node.cpp.o.requires

CMakeFiles/four-in-a-row.dir/node.cpp.o.provides: CMakeFiles/four-in-a-row.dir/node.cpp.o.requires
	$(MAKE) -f CMakeFiles/four-in-a-row.dir/build.make CMakeFiles/four-in-a-row.dir/node.cpp.o.provides.build
.PHONY : CMakeFiles/four-in-a-row.dir/node.cpp.o.provides

CMakeFiles/four-in-a-row.dir/node.cpp.o.provides.build: CMakeFiles/four-in-a-row.dir/node.cpp.o


# Object files for target four-in-a-row
four__in__a__row_OBJECTS = \
"CMakeFiles/four-in-a-row.dir/main.cpp.o" \
"CMakeFiles/four-in-a-row.dir/c4.cpp.o" \
"CMakeFiles/four-in-a-row.dir/c4bot.cpp.o" \
"CMakeFiles/four-in-a-row.dir/node.cpp.o"

# External object files for target four-in-a-row
four__in__a__row_EXTERNAL_OBJECTS =

four-in-a-row.exe: CMakeFiles/four-in-a-row.dir/main.cpp.o
four-in-a-row.exe: CMakeFiles/four-in-a-row.dir/c4.cpp.o
four-in-a-row.exe: CMakeFiles/four-in-a-row.dir/c4bot.cpp.o
four-in-a-row.exe: CMakeFiles/four-in-a-row.dir/node.cpp.o
four-in-a-row.exe: CMakeFiles/four-in-a-row.dir/build.make
four-in-a-row.exe: CMakeFiles/four-in-a-row.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable four-in-a-row.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/four-in-a-row.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/four-in-a-row.dir/build: four-in-a-row.exe

.PHONY : CMakeFiles/four-in-a-row.dir/build

CMakeFiles/four-in-a-row.dir/requires: CMakeFiles/four-in-a-row.dir/main.cpp.o.requires
CMakeFiles/four-in-a-row.dir/requires: CMakeFiles/four-in-a-row.dir/c4.cpp.o.requires
CMakeFiles/four-in-a-row.dir/requires: CMakeFiles/four-in-a-row.dir/c4bot.cpp.o.requires
CMakeFiles/four-in-a-row.dir/requires: CMakeFiles/four-in-a-row.dir/node.cpp.o.requires

.PHONY : CMakeFiles/four-in-a-row.dir/requires

CMakeFiles/four-in-a-row.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/four-in-a-row.dir/cmake_clean.cmake
.PHONY : CMakeFiles/four-in-a-row.dir/clean

CMakeFiles/four-in-a-row.dir/depend:
	cd /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/cmake-build-debug /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/cmake-build-debug /cygdrive/c/Users/renda/Desktop/Git/four-in-a-row/cmake-build-debug/CMakeFiles/four-in-a-row.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/four-in-a-row.dir/depend

