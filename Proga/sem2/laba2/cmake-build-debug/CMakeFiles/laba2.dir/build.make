# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /snap/clion/100/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/100/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vadim/CLionProjects/laba2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vadim/CLionProjects/laba2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/laba2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/laba2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/laba2.dir/flags.make

CMakeFiles/laba2.dir/main.cpp.o: CMakeFiles/laba2.dir/flags.make
CMakeFiles/laba2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vadim/CLionProjects/laba2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/laba2.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/laba2.dir/main.cpp.o -c /home/vadim/CLionProjects/laba2/main.cpp

CMakeFiles/laba2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/laba2.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vadim/CLionProjects/laba2/main.cpp > CMakeFiles/laba2.dir/main.cpp.i

CMakeFiles/laba2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/laba2.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vadim/CLionProjects/laba2/main.cpp -o CMakeFiles/laba2.dir/main.cpp.s

CMakeFiles/laba2.dir/SquarePolynomial.cpp.o: CMakeFiles/laba2.dir/flags.make
CMakeFiles/laba2.dir/SquarePolynomial.cpp.o: ../SquarePolynomial.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vadim/CLionProjects/laba2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/laba2.dir/SquarePolynomial.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/laba2.dir/SquarePolynomial.cpp.o -c /home/vadim/CLionProjects/laba2/SquarePolynomial.cpp

CMakeFiles/laba2.dir/SquarePolynomial.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/laba2.dir/SquarePolynomial.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vadim/CLionProjects/laba2/SquarePolynomial.cpp > CMakeFiles/laba2.dir/SquarePolynomial.cpp.i

CMakeFiles/laba2.dir/SquarePolynomial.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/laba2.dir/SquarePolynomial.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vadim/CLionProjects/laba2/SquarePolynomial.cpp -o CMakeFiles/laba2.dir/SquarePolynomial.cpp.s

# Object files for target laba2
laba2_OBJECTS = \
"CMakeFiles/laba2.dir/main.cpp.o" \
"CMakeFiles/laba2.dir/SquarePolynomial.cpp.o"

# External object files for target laba2
laba2_EXTERNAL_OBJECTS =

laba2: CMakeFiles/laba2.dir/main.cpp.o
laba2: CMakeFiles/laba2.dir/SquarePolynomial.cpp.o
laba2: CMakeFiles/laba2.dir/build.make
laba2: CMakeFiles/laba2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vadim/CLionProjects/laba2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable laba2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/laba2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/laba2.dir/build: laba2

.PHONY : CMakeFiles/laba2.dir/build

CMakeFiles/laba2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/laba2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/laba2.dir/clean

CMakeFiles/laba2.dir/depend:
	cd /home/vadim/CLionProjects/laba2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vadim/CLionProjects/laba2 /home/vadim/CLionProjects/laba2 /home/vadim/CLionProjects/laba2/cmake-build-debug /home/vadim/CLionProjects/laba2/cmake-build-debug /home/vadim/CLionProjects/laba2/cmake-build-debug/CMakeFiles/laba2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/laba2.dir/depend
