# Game /
# CMakeList.txt
#
cmake_minimum_required(	VERSION 3.23)

link_directories(		# SFML
						# msvc libs copied from submodule
									${CMAKE_CURRENT_LIST_DIR}/lib
)

add_custom_target(		copy_assets
									# Uncomment one to Copy fonts to msvc/ OR out/
									# unfortunately this is the only way I can get this to work
									COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Fonts
									${CMAKE_CURRENT_BINARY_DIR}/Fonts # Visual Studio Generator
									#$<TARGET_FILE_DIR:Game>/Fonts # CMake Project
)

# Game
add_executable (		Game
									"Main.cpp"
									"Game.cpp"
									"Game.h"
)

add_dependencies(		Game		copy_assets)

set_property(			TARGET 		Game
						PROPERTY 	CXX_STANDARD 20
)

# SFML
add_subdirectory(					"vendor/SFML")

target_link_libraries(
						Game 	
							PUBLIC
									# System Links
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