# CMakeList.txt : Top-Level
#
cmake_minimum_required( VERSION                 3.24)

# get OpenGL from OS
find_package(           "OpenGL"                REQUIRED)
include_directories(    ${OPENGL_INCLUDE_DIRS})

# Project
project(                "Game")
add_subdirectory(       "Game/")
set_property(           DIRECTORY               PROPERTY
                        VS_STARTUP_PROJECT      "Game"
)
