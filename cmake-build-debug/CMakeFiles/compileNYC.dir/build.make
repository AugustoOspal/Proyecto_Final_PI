# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/augusto/ITBA/Proyecto_Final_PI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/augusto/ITBA/Proyecto_Final_PI/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/compileNYC.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/compileNYC.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/compileNYC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compileNYC.dir/flags.make

CMakeFiles/compileNYC.dir/main.c.o: CMakeFiles/compileNYC.dir/flags.make
CMakeFiles/compileNYC.dir/main.c.o: ../main.c
CMakeFiles/compileNYC.dir/main.c.o: CMakeFiles/compileNYC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/augusto/ITBA/Proyecto_Final_PI/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/compileNYC.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compileNYC.dir/main.c.o -MF CMakeFiles/compileNYC.dir/main.c.o.d -o CMakeFiles/compileNYC.dir/main.c.o -c /home/augusto/ITBA/Proyecto_Final_PI/main.c

CMakeFiles/compileNYC.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/compileNYC.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/augusto/ITBA/Proyecto_Final_PI/main.c > CMakeFiles/compileNYC.dir/main.c.i

CMakeFiles/compileNYC.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/compileNYC.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/augusto/ITBA/Proyecto_Final_PI/main.c -o CMakeFiles/compileNYC.dir/main.c.s

CMakeFiles/compileNYC.dir/Library/helpers.c.o: CMakeFiles/compileNYC.dir/flags.make
CMakeFiles/compileNYC.dir/Library/helpers.c.o: ../Library/helpers.c
CMakeFiles/compileNYC.dir/Library/helpers.c.o: CMakeFiles/compileNYC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/augusto/ITBA/Proyecto_Final_PI/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/compileNYC.dir/Library/helpers.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compileNYC.dir/Library/helpers.c.o -MF CMakeFiles/compileNYC.dir/Library/helpers.c.o.d -o CMakeFiles/compileNYC.dir/Library/helpers.c.o -c /home/augusto/ITBA/Proyecto_Final_PI/Library/helpers.c

CMakeFiles/compileNYC.dir/Library/helpers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/compileNYC.dir/Library/helpers.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/augusto/ITBA/Proyecto_Final_PI/Library/helpers.c > CMakeFiles/compileNYC.dir/Library/helpers.c.i

CMakeFiles/compileNYC.dir/Library/helpers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/compileNYC.dir/Library/helpers.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/augusto/ITBA/Proyecto_Final_PI/Library/helpers.c -o CMakeFiles/compileNYC.dir/Library/helpers.c.s

CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.o: CMakeFiles/compileNYC.dir/flags.make
CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.o: ../Library/infractionSystemADT.c
CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.o: CMakeFiles/compileNYC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/augusto/ITBA/Proyecto_Final_PI/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.o -MF CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.o.d -o CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.o -c /home/augusto/ITBA/Proyecto_Final_PI/Library/infractionSystemADT.c

CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/augusto/ITBA/Proyecto_Final_PI/Library/infractionSystemADT.c > CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.i

CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/augusto/ITBA/Proyecto_Final_PI/Library/infractionSystemADT.c -o CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.s

CMakeFiles/compileNYC.dir/Library/htmlTable.c.o: CMakeFiles/compileNYC.dir/flags.make
CMakeFiles/compileNYC.dir/Library/htmlTable.c.o: ../Library/htmlTable.c
CMakeFiles/compileNYC.dir/Library/htmlTable.c.o: CMakeFiles/compileNYC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/augusto/ITBA/Proyecto_Final_PI/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/compileNYC.dir/Library/htmlTable.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compileNYC.dir/Library/htmlTable.c.o -MF CMakeFiles/compileNYC.dir/Library/htmlTable.c.o.d -o CMakeFiles/compileNYC.dir/Library/htmlTable.c.o -c /home/augusto/ITBA/Proyecto_Final_PI/Library/htmlTable.c

CMakeFiles/compileNYC.dir/Library/htmlTable.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/compileNYC.dir/Library/htmlTable.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/augusto/ITBA/Proyecto_Final_PI/Library/htmlTable.c > CMakeFiles/compileNYC.dir/Library/htmlTable.c.i

CMakeFiles/compileNYC.dir/Library/htmlTable.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/compileNYC.dir/Library/htmlTable.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/augusto/ITBA/Proyecto_Final_PI/Library/htmlTable.c -o CMakeFiles/compileNYC.dir/Library/htmlTable.c.s

# Object files for target compileNYC
compileNYC_OBJECTS = \
"CMakeFiles/compileNYC.dir/main.c.o" \
"CMakeFiles/compileNYC.dir/Library/helpers.c.o" \
"CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.o" \
"CMakeFiles/compileNYC.dir/Library/htmlTable.c.o"

# External object files for target compileNYC
compileNYC_EXTERNAL_OBJECTS =

compileNYC: CMakeFiles/compileNYC.dir/main.c.o
compileNYC: CMakeFiles/compileNYC.dir/Library/helpers.c.o
compileNYC: CMakeFiles/compileNYC.dir/Library/infractionSystemADT.c.o
compileNYC: CMakeFiles/compileNYC.dir/Library/htmlTable.c.o
compileNYC: CMakeFiles/compileNYC.dir/build.make
compileNYC: CMakeFiles/compileNYC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/augusto/ITBA/Proyecto_Final_PI/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable compileNYC"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compileNYC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compileNYC.dir/build: compileNYC
.PHONY : CMakeFiles/compileNYC.dir/build

CMakeFiles/compileNYC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compileNYC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compileNYC.dir/clean

CMakeFiles/compileNYC.dir/depend:
	cd /home/augusto/ITBA/Proyecto_Final_PI/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/augusto/ITBA/Proyecto_Final_PI /home/augusto/ITBA/Proyecto_Final_PI /home/augusto/ITBA/Proyecto_Final_PI/cmake-build-debug /home/augusto/ITBA/Proyecto_Final_PI/cmake-build-debug /home/augusto/ITBA/Proyecto_Final_PI/cmake-build-debug/CMakeFiles/compileNYC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compileNYC.dir/depend

