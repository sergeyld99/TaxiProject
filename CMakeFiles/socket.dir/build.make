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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject"

# Include any dependencies generated for this target.
include CMakeFiles/socket.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/socket.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/socket.dir/flags.make

CMakeFiles/socket.dir/socket.c.o: CMakeFiles/socket.dir/flags.make
CMakeFiles/socket.dir/socket.c.o: socket.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/socket.dir/socket.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/socket.dir/socket.c.o   -c "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/socket.c"

CMakeFiles/socket.dir/socket.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/socket.dir/socket.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/socket.c" > CMakeFiles/socket.dir/socket.c.i

CMakeFiles/socket.dir/socket.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/socket.dir/socket.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/socket.c" -o CMakeFiles/socket.dir/socket.c.s

CMakeFiles/socket.dir/socket.c.o.requires:

.PHONY : CMakeFiles/socket.dir/socket.c.o.requires

CMakeFiles/socket.dir/socket.c.o.provides: CMakeFiles/socket.dir/socket.c.o.requires
	$(MAKE) -f CMakeFiles/socket.dir/build.make CMakeFiles/socket.dir/socket.c.o.provides.build
.PHONY : CMakeFiles/socket.dir/socket.c.o.provides

CMakeFiles/socket.dir/socket.c.o.provides.build: CMakeFiles/socket.dir/socket.c.o


# Object files for target socket
socket_OBJECTS = \
"CMakeFiles/socket.dir/socket.c.o"

# External object files for target socket
socket_EXTERNAL_OBJECTS =

libsocket.a: CMakeFiles/socket.dir/socket.c.o
libsocket.a: CMakeFiles/socket.dir/build.make
libsocket.a: CMakeFiles/socket.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libsocket.a"
	$(CMAKE_COMMAND) -P CMakeFiles/socket.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/socket.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/socket.dir/build: libsocket.a

.PHONY : CMakeFiles/socket.dir/build

CMakeFiles/socket.dir/requires: CMakeFiles/socket.dir/socket.c.o.requires

.PHONY : CMakeFiles/socket.dir/requires

CMakeFiles/socket.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/socket.dir/cmake_clean.cmake
.PHONY : CMakeFiles/socket.dir/clean

CMakeFiles/socket.dir/depend:
	cd "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/CMakeFiles/socket.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/socket.dir/depend

