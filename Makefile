# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/CMakeFiles" "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/CMakeFiles/progress.marks"
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start "/home/dsl/Downloads/MyPrograms/Тестовые задания/Eltex/Projects/TaxiProject/CMakeFiles" 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named packet

# Build rule for target.
packet: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 packet
.PHONY : packet

# fast build rule for target.
packet/fast:
	$(MAKE) -f CMakeFiles/packet.dir/build.make CMakeFiles/packet.dir/build
.PHONY : packet/fast

#=============================================================================
# Target rules for targets named socket

# Build rule for target.
socket: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 socket
.PHONY : socket

# fast build rule for target.
socket/fast:
	$(MAKE) -f CMakeFiles/socket.dir/build.make CMakeFiles/socket.dir/build
.PHONY : socket/fast

#=============================================================================
# Target rules for targets named m_server

# Build rule for target.
m_server: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 m_server
.PHONY : m_server

# fast build rule for target.
m_server/fast:
	$(MAKE) -f CMakeFiles/m_server.dir/build.make CMakeFiles/m_server.dir/build
.PHONY : m_server/fast

#=============================================================================
# Target rules for targets named m_client

# Build rule for target.
m_client: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 m_client
.PHONY : m_client

# fast build rule for target.
m_client/fast:
	$(MAKE) -f CMakeFiles/m_client.dir/build.make CMakeFiles/m_client.dir/build
.PHONY : m_client/fast

main.o: main.c.o

.PHONY : main.o

# target to build an object file
main.c.o:
	$(MAKE) -f CMakeFiles/m_server.dir/build.make CMakeFiles/m_server.dir/main.c.o
.PHONY : main.c.o

main.i: main.c.i

.PHONY : main.i

# target to preprocess a source file
main.c.i:
	$(MAKE) -f CMakeFiles/m_server.dir/build.make CMakeFiles/m_server.dir/main.c.i
.PHONY : main.c.i

main.s: main.c.s

.PHONY : main.s

# target to generate assembly for a file
main.c.s:
	$(MAKE) -f CMakeFiles/m_server.dir/build.make CMakeFiles/m_server.dir/main.c.s
.PHONY : main.c.s

main_client.o: main_client.c.o

.PHONY : main_client.o

# target to build an object file
main_client.c.o:
	$(MAKE) -f CMakeFiles/m_client.dir/build.make CMakeFiles/m_client.dir/main_client.c.o
.PHONY : main_client.c.o

main_client.i: main_client.c.i

.PHONY : main_client.i

# target to preprocess a source file
main_client.c.i:
	$(MAKE) -f CMakeFiles/m_client.dir/build.make CMakeFiles/m_client.dir/main_client.c.i
.PHONY : main_client.c.i

main_client.s: main_client.c.s

.PHONY : main_client.s

# target to generate assembly for a file
main_client.c.s:
	$(MAKE) -f CMakeFiles/m_client.dir/build.make CMakeFiles/m_client.dir/main_client.c.s
.PHONY : main_client.c.s

packet.o: packet.c.o

.PHONY : packet.o

# target to build an object file
packet.c.o:
	$(MAKE) -f CMakeFiles/packet.dir/build.make CMakeFiles/packet.dir/packet.c.o
.PHONY : packet.c.o

packet.i: packet.c.i

.PHONY : packet.i

# target to preprocess a source file
packet.c.i:
	$(MAKE) -f CMakeFiles/packet.dir/build.make CMakeFiles/packet.dir/packet.c.i
.PHONY : packet.c.i

packet.s: packet.c.s

.PHONY : packet.s

# target to generate assembly for a file
packet.c.s:
	$(MAKE) -f CMakeFiles/packet.dir/build.make CMakeFiles/packet.dir/packet.c.s
.PHONY : packet.c.s

socket.o: socket.c.o

.PHONY : socket.o

# target to build an object file
socket.c.o:
	$(MAKE) -f CMakeFiles/socket.dir/build.make CMakeFiles/socket.dir/socket.c.o
.PHONY : socket.c.o

socket.i: socket.c.i

.PHONY : socket.i

# target to preprocess a source file
socket.c.i:
	$(MAKE) -f CMakeFiles/socket.dir/build.make CMakeFiles/socket.dir/socket.c.i
.PHONY : socket.c.i

socket.s: socket.c.s

.PHONY : socket.s

# target to generate assembly for a file
socket.c.s:
	$(MAKE) -f CMakeFiles/socket.dir/build.make CMakeFiles/socket.dir/socket.c.s
.PHONY : socket.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... packet"
	@echo "... socket"
	@echo "... m_server"
	@echo "... m_client"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... main_client.o"
	@echo "... main_client.i"
	@echo "... main_client.s"
	@echo "... packet.o"
	@echo "... packet.i"
	@echo "... packet.s"
	@echo "... socket.o"
	@echo "... socket.i"
	@echo "... socket.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
