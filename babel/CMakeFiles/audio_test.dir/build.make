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
include babel/CMakeFiles/audio_test.dir/depend.make

# Include the progress variables for this target.
include babel/CMakeFiles/audio_test.dir/progress.make

# Include the compile flags for this target's objects.
include babel/CMakeFiles/audio_test.dir/flags.make

babel/CMakeFiles/audio_test.dir/srcs/main.cpp.o: babel/CMakeFiles/audio_test.dir/flags.make
babel/CMakeFiles/audio_test.dir/srcs/main.cpp.o: babel/srcs/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camille_bouzerand/Repository/OOP/Babel_2019/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object babel/CMakeFiles/audio_test.dir/srcs/main.cpp.o"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/babel && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/audio_test.dir/srcs/main.cpp.o -c /home/camille_bouzerand/Repository/OOP/Babel_2019/babel/srcs/main.cpp

babel/CMakeFiles/audio_test.dir/srcs/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/audio_test.dir/srcs/main.cpp.i"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/babel && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/camille_bouzerand/Repository/OOP/Babel_2019/babel/srcs/main.cpp > CMakeFiles/audio_test.dir/srcs/main.cpp.i

babel/CMakeFiles/audio_test.dir/srcs/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/audio_test.dir/srcs/main.cpp.s"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/babel && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/camille_bouzerand/Repository/OOP/Babel_2019/babel/srcs/main.cpp -o CMakeFiles/audio_test.dir/srcs/main.cpp.s

# Object files for target audio_test
audio_test_OBJECTS = \
"CMakeFiles/audio_test.dir/srcs/main.cpp.o"

# External object files for target audio_test
audio_test_EXTERNAL_OBJECTS =

audio_test: babel/CMakeFiles/audio_test.dir/srcs/main.cpp.o
audio_test: babel/CMakeFiles/audio_test.dir/build.make
audio_test: /home/camille_bouzerand/.conan/data/qt/5.12.5/bincrafters/stable/package/b5df9c5f99a00fb653b3b237ecc767ee6c61bfc5/lib/libQt5Widgets.so.5.12.5
audio_test: /home/camille_bouzerand/.conan/data/qt/5.12.5/bincrafters/stable/package/b5df9c5f99a00fb653b3b237ecc767ee6c61bfc5/lib/libQt5Gui.so.5.12.5
audio_test: /home/camille_bouzerand/.conan/data/qt/5.12.5/bincrafters/stable/package/b5df9c5f99a00fb653b3b237ecc767ee6c61bfc5/lib/libQt5Core.so.5.12.5
audio_test: babel/CMakeFiles/audio_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/camille_bouzerand/Repository/OOP/Babel_2019/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../audio_test"
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/babel && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/audio_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
babel/CMakeFiles/audio_test.dir/build: audio_test

.PHONY : babel/CMakeFiles/audio_test.dir/build

babel/CMakeFiles/audio_test.dir/clean:
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019/babel && $(CMAKE_COMMAND) -P CMakeFiles/audio_test.dir/cmake_clean.cmake
.PHONY : babel/CMakeFiles/audio_test.dir/clean

babel/CMakeFiles/audio_test.dir/depend:
	cd /home/camille_bouzerand/Repository/OOP/Babel_2019 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/camille_bouzerand/Repository/OOP/Babel_2019 /home/camille_bouzerand/Repository/OOP/Babel_2019/babel /home/camille_bouzerand/Repository/OOP/Babel_2019 /home/camille_bouzerand/Repository/OOP/Babel_2019/babel /home/camille_bouzerand/Repository/OOP/Babel_2019/babel/CMakeFiles/audio_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : babel/CMakeFiles/audio_test.dir/depend

