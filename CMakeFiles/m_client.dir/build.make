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
include CMakeFiles/m_client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/m_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/m_client.dir/flags.make

CMakeFiles/m_client.dir/main_client.c.o: CMakeFiles/m_client.dir/flags.make
CMakeFiles/m_client.dir/main_client.c.o: main_client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/m_client.dir/main_client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/m_client.dir/main_client.c.o   -c "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/main_client.c"

CMakeFiles/m_client.dir/main_client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/m_client.dir/main_client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/main_client.c" > CMakeFiles/m_client.dir/main_client.c.i

CMakeFiles/m_client.dir/main_client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/m_client.dir/main_client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/main_client.c" -o CMakeFiles/m_client.dir/main_client.c.s

CMakeFiles/m_client.dir/main_client.c.o.requires:

.PHONY : CMakeFiles/m_client.dir/main_client.c.o.requires

CMakeFiles/m_client.dir/main_client.c.o.provides: CMakeFiles/m_client.dir/main_client.c.o.requires
	$(MAKE) -f CMakeFiles/m_client.dir/build.make CMakeFiles/m_client.dir/main_client.c.o.provides.build
.PHONY : CMakeFiles/m_client.dir/main_client.c.o.provides

CMakeFiles/m_client.dir/main_client.c.o.provides.build: CMakeFiles/m_client.dir/main_client.c.o


# Object files for target m_client
m_client_OBJECTS = \
"CMakeFiles/m_client.dir/main_client.c.o"

# External object files for target m_client
m_client_EXTERNAL_OBJECTS =

m_client: CMakeFiles/m_client.dir/main_client.c.o
m_client: CMakeFiles/m_client.dir/build.make
m_client: libsocket.a
m_client: libpacket.a
m_client: CMakeFiles/m_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable m_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/m_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/m_client.dir/build: m_client

.PHONY : CMakeFiles/m_client.dir/build

CMakeFiles/m_client.dir/requires: CMakeFiles/m_client.dir/main_client.c.o.requires

.PHONY : CMakeFiles/m_client.dir/requires

CMakeFiles/m_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/m_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/m_client.dir/clean

CMakeFiles/m_client.dir/depend:
	cd "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/CMakeFiles/m_client.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/m_client.dir/depend
