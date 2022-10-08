# Game /
# CMakeList.txt

cmake_minimum_required(	VERSION 	3.23)

link_directories(					# Dependencies
									# copied from `extlibs/libs-msvc`
									${CMAKE_CURRENT_LIST_DIR}/lib
)

add_custom_target(		copy_fonts	# Visual Studio Generator from CMake [-G]
									COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Fonts
									${CMAKE_CURRENT_BINARY_DIR}/Fonts

									# CMake Project Generated from Visual Studio [Open Visual Studio Here]
									COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Fonts
									$<TARGET_FILE_DIR:Game>/Fonts
)

									
add_executable (		Game		# Game Executable
									"Main.cpp"
									"Game.cpp"
									"Game.h"
)

add_dependencies(		Game		copy_fonts)

set_property(			TARGET 		Game
						PROPERTY 	CXX_STANDARD 20
)

									
add_subdirectory(					# Submodules
									"vendor/SFML"
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

# TODO: Add tests and install targets if needed.