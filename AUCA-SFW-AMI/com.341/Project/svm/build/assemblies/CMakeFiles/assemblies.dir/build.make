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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hrafnulf/Documents/OS2017/Project/svm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hrafnulf/Documents/OS2017/Project/svm/build

# Utility rule file for assemblies.

# Include the progress variables for this target.
include assemblies/CMakeFiles/assemblies.dir/progress.make

assemblies/CMakeFiles/assemblies: assemblies/change_registers_and_exit.vmexe
assemblies/CMakeFiles/assemblies: assemblies/write_to_register_in_loop.vmexe


assemblies/change_registers_and_exit.vmexe: svmasm/svmasm
assemblies/change_registers_and_exit.vmexe: ../assemblies/change_registers_and_exit.vmasm
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/hrafnulf/Documents/OS2017/Project/svm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating change_registers_and_exit.vmexe"
	cd /home/hrafnulf/Documents/OS2017/Project/svm/build/assemblies && /home/hrafnulf/Documents/OS2017/Project/svm/build/svmasm/svmasm /home/hrafnulf/Documents/OS2017/Project/svm/assemblies/change_registers_and_exit.vmasm change_registers_and_exit.vmexe

assemblies/write_to_register_in_loop.vmexe: svmasm/svmasm
assemblies/write_to_register_in_loop.vmexe: ../assemblies/write_to_register_in_loop.vmasm
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/hrafnulf/Documents/OS2017/Project/svm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating write_to_register_in_loop.vmexe"
	cd /home/hrafnulf/Documents/OS2017/Project/svm/build/assemblies && /home/hrafnulf/Documents/OS2017/Project/svm/build/svmasm/svmasm /home/hrafnulf/Documents/OS2017/Project/svm/assemblies/write_to_register_in_loop.vmasm write_to_register_in_loop.vmexe

assemblies: assemblies/CMakeFiles/assemblies
assemblies: assemblies/change_registers_and_exit.vmexe
assemblies: assemblies/write_to_register_in_loop.vmexe
assemblies: assemblies/CMakeFiles/assemblies.dir/build.make

.PHONY : assemblies

# Rule to build all files generated by this target.
assemblies/CMakeFiles/assemblies.dir/build: assemblies

.PHONY : assemblies/CMakeFiles/assemblies.dir/build

assemblies/CMakeFiles/assemblies.dir/clean:
	cd /home/hrafnulf/Documents/OS2017/Project/svm/build/assemblies && $(CMAKE_COMMAND) -P CMakeFiles/assemblies.dir/cmake_clean.cmake
.PHONY : assemblies/CMakeFiles/assemblies.dir/clean

assemblies/CMakeFiles/assemblies.dir/depend:
	cd /home/hrafnulf/Documents/OS2017/Project/svm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hrafnulf/Documents/OS2017/Project/svm /home/hrafnulf/Documents/OS2017/Project/svm/assemblies /home/hrafnulf/Documents/OS2017/Project/svm/build /home/hrafnulf/Documents/OS2017/Project/svm/build/assemblies /home/hrafnulf/Documents/OS2017/Project/svm/build/assemblies/CMakeFiles/assemblies.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : assemblies/CMakeFiles/assemblies.dir/depend

