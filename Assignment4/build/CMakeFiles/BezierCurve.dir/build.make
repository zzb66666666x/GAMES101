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
CMAKE_SOURCE_DIR = D:\Mycode\Cpp\GAMES101\Assignment4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Mycode\Cpp\GAMES101\Assignment4\build

# Include any dependencies generated for this target.
include CMakeFiles/BezierCurve.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BezierCurve.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BezierCurve.dir/flags.make

CMakeFiles/BezierCurve.dir/main.cpp.obj: CMakeFiles/BezierCurve.dir/flags.make
CMakeFiles/BezierCurve.dir/main.cpp.obj: CMakeFiles/BezierCurve.dir/includes_CXX.rsp
CMakeFiles/BezierCurve.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Mycode\Cpp\GAMES101\Assignment4\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BezierCurve.dir/main.cpp.obj"
	D:\MinGW\TDM64GCC\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\BezierCurve.dir\main.cpp.obj -c D:\Mycode\Cpp\GAMES101\Assignment4\main.cpp

CMakeFiles/BezierCurve.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BezierCurve.dir/main.cpp.i"
	D:\MinGW\TDM64GCC\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Mycode\Cpp\GAMES101\Assignment4\main.cpp > CMakeFiles\BezierCurve.dir\main.cpp.i

CMakeFiles/BezierCurve.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BezierCurve.dir/main.cpp.s"
	D:\MinGW\TDM64GCC\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Mycode\Cpp\GAMES101\Assignment4\main.cpp -o CMakeFiles\BezierCurve.dir\main.cpp.s

# Object files for target BezierCurve
BezierCurve_OBJECTS = \
"CMakeFiles/BezierCurve.dir/main.cpp.obj"

# External object files for target BezierCurve
BezierCurve_EXTERNAL_OBJECTS =

BezierCurve.exe: CMakeFiles/BezierCurve.dir/main.cpp.obj
BezierCurve.exe: CMakeFiles/BezierCurve.dir/build.make
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_dnn440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_gapi440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_highgui440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_ml440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_objdetect440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_photo440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_stitching440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_video440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_videoio440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_imgcodecs440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_calib3d440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_features2d440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_flann440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_imgproc440.dll.a
BezierCurve.exe: D:/CodingLibs/opencv/mingw_build/lib/libopencv_core440.dll.a
BezierCurve.exe: CMakeFiles/BezierCurve.dir/linklibs.rsp
BezierCurve.exe: CMakeFiles/BezierCurve.dir/objects1.rsp
BezierCurve.exe: CMakeFiles/BezierCurve.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Mycode\Cpp\GAMES101\Assignment4\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable BezierCurve.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\BezierCurve.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BezierCurve.dir/build: BezierCurve.exe

.PHONY : CMakeFiles/BezierCurve.dir/build

CMakeFiles/BezierCurve.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\BezierCurve.dir\cmake_clean.cmake
.PHONY : CMakeFiles/BezierCurve.dir/clean

CMakeFiles/BezierCurve.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Mycode\Cpp\GAMES101\Assignment4 D:\Mycode\Cpp\GAMES101\Assignment4 D:\Mycode\Cpp\GAMES101\Assignment4\build D:\Mycode\Cpp\GAMES101\Assignment4\build D:\Mycode\Cpp\GAMES101\Assignment4\build\CMakeFiles\BezierCurve.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BezierCurve.dir/depend
