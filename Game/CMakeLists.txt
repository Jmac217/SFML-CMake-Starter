# Game /
# CMakeList.txt

cmake_minimum_required(	VERSION 	3.24)

link_directories(					# Dependencies
									# copied from `extlibs/libs-msvc`
									${CMAKE_CURRENT_LIST_DIR}/lib
)

add_custom_target(		copy_media	# Visual Studio Generator from CMake [-G]
									# Copy Media/
									COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Media
									${CMAKE_CURRENT_BINARY_DIR}/Media

									# CMake Project Generated from Visual Studio [Open Visual Studio Here]
									# Copy Media/
									COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Media
									$<TARGET_FILE_DIR:Game>/Media
)

add_executable (		Game		# Game Executable
									"pch.cpp"
									"pch.h"
									"Main.cpp"
									"Game.cpp"
									"Game.h"
)

add_dependencies(		Game		copy_media)

set_property(			TARGET 		Game
						PROPERTY 	CXX_STANDARD	20
)

add_subdirectory(					# Submodules
									"vendor/SFML"
)

target_precompile_headers(
						Game
							PUBLIC
									"pch.h"
)

target_link_libraries(				# Links
						Game 	
							PUBLIC
									# System
									opengl32
									gdi32
									ws2_32
									winmm

									# SFML
									sfml-system
									sfml-window
									sfml-graphics
									sfml-audio
									sfml-network
)

# TODO: Add tests and install targets when needed.