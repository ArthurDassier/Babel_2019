# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_SOURCE_DIR = /home/camille_bouzerand/Repository/OOP/Babel_2019

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/camille_bouzerand/Repository/OOP/Babel_2019

# Include any dependencies generated for this target.
include client_interface/CMakeFiles/interface.dir/depend.make

# Include the progress variables for this target.
include client_interface/CMakeFiles/interface.dir/progress.make

# Include the compile flags for this target's objects.
include client_interface/CMakeFiles/interface.dir/flags.make

client_interface/include/moc_mainwindow.cpp: client_interface/include/mainwindow.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/camille_bouzerand/Repository/OOP/Babel_2019/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating include/moc_mainwindow.cpp"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/include && /home/camille_bouzerand/.conan/data/qt/5.12.5/bincrafters/stable/package/b5df9c5f99a00fb653b3b237ecc767ee6c61bfc5/bin/moc @/home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/include/moc_mainwindow.cpp_parameters

client_interface/CMakeFiles/interface.dir/main.cpp.o: client_interface/CMakeFiles/interface.dir/flags.make
client_interface/CMakeFiles/interface.dir/main.cpp.o: client_interface/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camille_bouzerand/Repository/OOP/Babel_2019/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object client_interface/CMakeFiles/interface.dir/main.cpp.o"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/interface.dir/main.cpp.o -c /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/main.cpp

client_interface/CMakeFiles/interface.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interface.dir/main.cpp.i"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/main.cpp > CMakeFiles/interface.dir/main.cpp.i

client_interface/CMakeFiles/interface.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interface.dir/main.cpp.s"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/main.cpp -o CMakeFiles/interface.dir/main.cpp.s

client_interface/CMakeFiles/interface.dir/mainwindow.cpp.o: client_interface/CMakeFiles/interface.dir/flags.make
client_interface/CMakeFiles/interface.dir/mainwindow.cpp.o: client_interface/mainwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camille_bouzerand/Repository/OOP/Babel_2019/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object client_interface/CMakeFiles/interface.dir/mainwindow.cpp.o"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/interface.dir/mainwindow.cpp.o -c /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/mainwindow.cpp

client_interface/CMakeFiles/interface.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interface.dir/mainwindow.cpp.i"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/mainwindow.cpp > CMakeFiles/interface.dir/mainwindow.cpp.i

client_interface/CMakeFiles/interface.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interface.dir/mainwindow.cpp.s"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/mainwindow.cpp -o CMakeFiles/interface.dir/mainwindow.cpp.s

client_interface/CMakeFiles/interface.dir/include/moc_mainwindow.cpp.o: client_interface/CMakeFiles/interface.dir/flags.make
client_interface/CMakeFiles/interface.dir/include/moc_mainwindow.cpp.o: client_interface/include/moc_mainwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camille_bouzerand/Repository/OOP/Babel_2019/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object client_interface/CMakeFiles/interface.dir/include/moc_mainwindow.cpp.o"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/interface.dir/include/moc_mainwindow.cpp.o -c /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/include/moc_mainwindow.cpp

client_interface/CMakeFiles/interface.dir/include/moc_mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interface.dir/include/moc_mainwindow.cpp.i"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/include/moc_mainwindow.cpp > CMakeFiles/interface.dir/include/moc_mainwindow.cpp.i

client_interface/CMakeFiles/interface.dir/include/moc_mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interface.dir/include/moc_mainwindow.cpp.s"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/include/moc_mainwindow.cpp -o CMakeFiles/interface.dir/include/moc_mainwindow.cpp.s

client_interface/CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o: client_interface/CMakeFiles/interface.dir/flags.make
client_interface/CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o: client_interface/interface_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camille_bouzerand/Repository/OOP/Babel_2019/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object client_interface/CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o -c /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/interface_autogen/mocs_compilation.cpp

client_interface/CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.i"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/interface_autogen/mocs_compilation.cpp > CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.i

client_interface/CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.s"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/interface_autogen/mocs_compilation.cpp -o CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.s

# Object files for target interface
interface_OBJECTS = \
"CMakeFiles/interface.dir/main.cpp.o" \
"CMakeFiles/interface.dir/mainwindow.cpp.o" \
"CMakeFiles/interface.dir/include/moc_mainwindow.cpp.o" \
"CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o"

# External object files for target interface
interface_EXTERNAL_OBJECTS =

interface: client_interface/CMakeFiles/interface.dir/main.cpp.o
interface: client_interface/CMakeFiles/interface.dir/mainwindow.cpp.o
interface: client_interface/CMakeFiles/interface.dir/include/moc_mainwindow.cpp.o
interface: client_interface/CMakeFiles/interface.dir/interface_autogen/mocs_compilation.cpp.o
interface: client_interface/CMakeFiles/interface.dir/build.make
interface: /home/camille_bouzerand/.conan/data/qt/5.12.5/bincrafters/stable/package/b5df9c5f99a00fb653b3b237ecc767ee6c61bfc5/lib/libQt5Widgets.so.5.12.5
interface: /home/camille_bouzerand/.conan/data/qt/5.12.5/bincrafters/stable/package/b5df9c5f99a00fb653b3b237ecc767ee6c61bfc5/lib/libQt5Gui.so.5.12.5
interface: /home/camille_bouzerand/.conan/data/qt/5.12.5/bincrafters/stable/package/b5df9c5f99a00fb653b3b237ecc767ee6c61bfc5/lib/libQt5Core.so.5.12.5
interface: client_interface/CMakeFiles/interface.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/camille_bouzerand/Repository/OOP/Babel_2019/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ../interface"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/interface.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
client_interface/CMakeFiles/interface.dir/build: interface

.PHONY : client_interface/CMakeFiles/interface.dir/build

client_interface/CMakeFiles/interface.dir/clean:
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface && $(CMAKE_COMMAND) -P CMakeFiles/interface.dir/cmake_clean.cmake
.PHONY : client_interface/CMakeFiles/interface.dir/clean

client_interface/CMakeFiles/interface.dir/depend: client_interface/include/moc_mainwindow.cpp
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/camille_bouzerand/Repository/OOP/Babel_2019 /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface /home/camille_bouzerand/Repository/OOP/Babel_2019 /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface /home/camille_bouzerand/Repository/OOP/Babel_2019/client_interface/CMakeFiles/interface.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : client_interface/CMakeFiles/interface.dir/depend

