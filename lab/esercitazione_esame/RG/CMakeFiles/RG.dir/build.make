# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/nonnt66/Scaricati/uni/elim/lab/esercitazione_esame/RG

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nonnt66/Scaricati/uni/elim/lab/esercitazione_esame/RG

# Include any dependencies generated for this target.
include CMakeFiles/RG.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RG.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RG.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RG.dir/flags.make

CMakeFiles/RG.dir/main.cpp.o: CMakeFiles/RG.dir/flags.make
CMakeFiles/RG.dir/main.cpp.o: main.cpp
CMakeFiles/RG.dir/main.cpp.o: CMakeFiles/RG.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/nonnt66/Scaricati/uni/elim/lab/esercitazione_esame/RG/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RG.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RG.dir/main.cpp.o -MF CMakeFiles/RG.dir/main.cpp.o.d -o CMakeFiles/RG.dir/main.cpp.o -c /home/nonnt66/Scaricati/uni/elim/lab/esercitazione_esame/RG/main.cpp

CMakeFiles/RG.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RG.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nonnt66/Scaricati/uni/elim/lab/esercitazione_esame/RG/main.cpp > CMakeFiles/RG.dir/main.cpp.i

CMakeFiles/RG.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RG.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nonnt66/Scaricati/uni/elim/lab/esercitazione_esame/RG/main.cpp -o CMakeFiles/RG.dir/main.cpp.s

# Object files for target RG
RG_OBJECTS = \
"CMakeFiles/RG.dir/main.cpp.o"

# External object files for target RG
RG_EXTERNAL_OBJECTS =

RG: CMakeFiles/RG.dir/main.cpp.o
RG: CMakeFiles/RG.dir/build.make
RG: /usr/local/lib/libopencv_gapi.so.4.10.0
RG: /usr/local/lib/libopencv_highgui.so.4.10.0
RG: /usr/local/lib/libopencv_ml.so.4.10.0
RG: /usr/local/lib/libopencv_objdetect.so.4.10.0
RG: /usr/local/lib/libopencv_photo.so.4.10.0
RG: /usr/local/lib/libopencv_stitching.so.4.10.0
RG: /usr/local/lib/libopencv_video.so.4.10.0
RG: /usr/local/lib/libopencv_videoio.so.4.10.0
RG: /usr/local/lib/libopencv_imgcodecs.so.4.10.0
RG: /usr/local/lib/libopencv_dnn.so.4.10.0
RG: /usr/local/lib/libopencv_calib3d.so.4.10.0
RG: /usr/local/lib/libopencv_features2d.so.4.10.0
RG: /usr/local/lib/libopencv_flann.so.4.10.0
RG: /usr/local/lib/libopencv_imgproc.so.4.10.0
RG: /usr/local/lib/libopencv_core.so.4.10.0
RG: CMakeFiles/RG.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/nonnt66/Scaricati/uni/elim/lab/esercitazione_esame/RG/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RG"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RG.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RG.dir/build: RG
.PHONY : CMakeFiles/RG.dir/build

CMakeFiles/RG.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RG.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RG.dir/clean

CMakeFiles/RG.dir/depend:
	cd /home/nonnt66/Scaricati/uni/elim/lab/esercitazione_esame/RG && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nonnt66/Scaricati/uni/elim/lab/esercitazione_esame/RG /home/nonnt66/Scaricati/uni/elim/lab/esercitazione_esame/RG /home/nonnt66/Scaricati/uni/elim/lab/esercitazione_esame/RG /home/nonnt66/Scaricati/uni/elim/lab/esercitazione_esame/RG /home/nonnt66/Scaricati/uni/elim/lab/esercitazione_esame/RG/CMakeFiles/RG.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/RG.dir/depend
