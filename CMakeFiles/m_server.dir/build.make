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
include CMakeFiles/m_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/m_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/m_server.dir/flags.make

CMakeFiles/m_server.dir/main.c.o: CMakeFiles/m_server.dir/flags.make
CMakeFiles/m_server.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/m_server.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/m_server.dir/main.c.o   -c "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/main.c"

CMakeFiles/m_server.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/m_server.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/main.c" > CMakeFiles/m_server.dir/main.c.i

CMakeFiles/m_server.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/m_server.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/main.c" -o CMakeFiles/m_server.dir/main.c.s

CMakeFiles/m_server.dir/main.c.o.requires:

.PHONY : CMakeFiles/m_server.dir/main.c.o.requires

CMakeFiles/m_server.dir/main.c.o.provides: CMakeFiles/m_server.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/m_server.dir/build.make CMakeFiles/m_server.dir/main.c.o.provides.build
.PHONY : CMakeFiles/m_server.dir/main.c.o.provides

CMakeFiles/m_server.dir/main.c.o.provides.build: CMakeFiles/m_server.dir/main.c.o


# Object files for target m_server
m_server_OBJECTS = \
"CMakeFiles/m_server.dir/main.c.o"

# External object files for target m_server
m_server_EXTERNAL_OBJECTS =

m_server: CMakeFiles/m_server.dir/main.c.o
m_server: CMakeFiles/m_server.dir/build.make
m_server: libsocket.a
m_server: libpacket.a
m_server: CMakeFiles/m_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable m_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/m_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/m_server.dir/build: m_server

.PHONY : CMakeFiles/m_server.dir/build

CMakeFiles/m_server.dir/requires: CMakeFiles/m_server.dir/main.c.o.requires

.PHONY : CMakeFiles/m_server.dir/requires

CMakeFiles/m_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/m_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/m_server.dir/clean

CMakeFiles/m_server.dir/depend:
	cd "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/CMakeFiles/m_server.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/m_server.dir/depend
