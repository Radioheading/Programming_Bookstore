# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/18221/CLionProjects/ACM_BOOKSTORE_PRE

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/18221/CLionProjects/ACM_BOOKSTORE_PRE/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ACM_BOOKSTORE_PRE.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ACM_BOOKSTORE_PRE.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ACM_BOOKSTORE_PRE.dir/flags.make

CMakeFiles/ACM_BOOKSTORE_PRE.dir/main.cpp.o: CMakeFiles/ACM_BOOKSTORE_PRE.dir/flags.make
CMakeFiles/ACM_BOOKSTORE_PRE.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/18221/CLionProjects/ACM_BOOKSTORE_PRE/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ACM_BOOKSTORE_PRE.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ACM_BOOKSTORE_PRE.dir/main.cpp.o -c /mnt/c/Users/18221/CLionProjects/ACM_BOOKSTORE_PRE/main.cpp

CMakeFiles/ACM_BOOKSTORE_PRE.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ACM_BOOKSTORE_PRE.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/18221/CLionProjects/ACM_BOOKSTORE_PRE/main.cpp > CMakeFiles/ACM_BOOKSTORE_PRE.dir/main.cpp.i

CMakeFiles/ACM_BOOKSTORE_PRE.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ACM_BOOKSTORE_PRE.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/18221/CLionProjects/ACM_BOOKSTORE_PRE/main.cpp -o CMakeFiles/ACM_BOOKSTORE_PRE.dir/main.cpp.s

# Object files for target ACM_BOOKSTORE_PRE
ACM_BOOKSTORE_PRE_OBJECTS = \
"CMakeFiles/ACM_BOOKSTORE_PRE.dir/main.cpp.o"

# External object files for target ACM_BOOKSTORE_PRE
ACM_BOOKSTORE_PRE_EXTERNAL_OBJECTS =

ACM_BOOKSTORE_PRE: CMakeFiles/ACM_BOOKSTORE_PRE.dir/main.cpp.o
ACM_BOOKSTORE_PRE: CMakeFiles/ACM_BOOKSTORE_PRE.dir/build.make
ACM_BOOKSTORE_PRE: CMakeFiles/ACM_BOOKSTORE_PRE.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/18221/CLionProjects/ACM_BOOKSTORE_PRE/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ACM_BOOKSTORE_PRE"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ACM_BOOKSTORE_PRE.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ACM_BOOKSTORE_PRE.dir/build: ACM_BOOKSTORE_PRE

.PHONY : CMakeFiles/ACM_BOOKSTORE_PRE.dir/build

CMakeFiles/ACM_BOOKSTORE_PRE.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ACM_BOOKSTORE_PRE.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ACM_BOOKSTORE_PRE.dir/clean

CMakeFiles/ACM_BOOKSTORE_PRE.dir/depend:
	cd /mnt/c/Users/18221/CLionProjects/ACM_BOOKSTORE_PRE/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/18221/CLionProjects/ACM_BOOKSTORE_PRE /mnt/c/Users/18221/CLionProjects/ACM_BOOKSTORE_PRE /mnt/c/Users/18221/CLionProjects/ACM_BOOKSTORE_PRE/cmake-build-debug /mnt/c/Users/18221/CLionProjects/ACM_BOOKSTORE_PRE/cmake-build-debug /mnt/c/Users/18221/CLionProjects/ACM_BOOKSTORE_PRE/cmake-build-debug/CMakeFiles/ACM_BOOKSTORE_PRE.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ACM_BOOKSTORE_PRE.dir/depend
