# CMakeList.txt : Top-Level
#
cmake_minimum_required (VERSION 3.23)

# get OpenGL from local computer
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Project
project ("Game")
add_subdirectory ("Game")
