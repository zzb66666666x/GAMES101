# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.18

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\CMake\bin\cmake.exe

# The command to remove a file.
RM = D:\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\MyCode\Cpp\GAMES101\testcv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\MyCode\Cpp\GAMES101\testcv\build

# Include any dependencies generated for this target.
include CMakeFiles/testcv.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testcv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testcv.dir/flags.make

CMakeFiles/testcv.dir/main.cpp.obj: CMakeFiles/testcv.dir/flags.make
CMakeFiles/testcv.dir/main.cpp.obj: CMakeFiles/testcv.dir/includes_CXX.rsp
CMakeFiles/testcv.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\MyCode\Cpp\GAMES101\testcv\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testcv.dir/main.cpp.obj"
	D:\MinGW\TDM64GCC\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\testcv.dir\main.cpp.obj -c D:\MyCode\Cpp\GAMES101\testcv\main.cpp

CMakeFiles/testcv.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testcv.dir/main.cpp.i"
	D:\MinGW\TDM64GCC\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\MyCode\Cpp\GAMES101\testcv\main.cpp > CMakeFiles\testcv.dir\main.cpp.i

CMakeFiles/testcv.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testcv.dir/main.cpp.s"
	D:\MinGW\TDM64GCC\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\MyCode\Cpp\GAMES101\testcv\main.cpp -o CMakeFiles\testcv.dir\main.cpp.s

# Object files for target testcv
testcv_OBJECTS = \
"CMakeFiles/testcv.dir/main.cpp.obj"

# External object files for target testcv
testcv_EXTERNAL_OBJECTS =

testcv.exe: CMakeFiles/testcv.dir/main.cpp.obj
testcv.exe: CMakeFiles/testcv.dir/build.make
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_dnn440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_gapi440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_highgui440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_ml440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_objdetect440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_photo440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_stitching440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_video440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_videoio440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_imgcodecs440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_calib3d440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_features2d440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_flann440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_imgproc440.dll.a
testcv.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_core440.dll.a
testcv.exe: CMakeFiles/testcv.dir/linklibs.rsp
testcv.exe: CMakeFiles/testcv.dir/objects1.rsp
testcv.exe: CMakeFiles/testcv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\MyCode\Cpp\GAMES101\testcv\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testcv.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\testcv.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testcv.dir/build: testcv.exe

.PHONY : CMakeFiles/testcv.dir/build

CMakeFiles/testcv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\testcv.dir\cmake_clean.cmake
.PHONY : CMakeFiles/testcv.dir/clean

CMakeFiles/testcv.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\MyCode\Cpp\GAMES101\testcv D:\MyCode\Cpp\GAMES101\testcv D:\MyCode\Cpp\GAMES101\testcv\build D:\MyCode\Cpp\GAMES101\testcv\build D:\MyCode\Cpp\GAMES101\testcv\build\CMakeFiles\testcv.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testcv.dir/depend

