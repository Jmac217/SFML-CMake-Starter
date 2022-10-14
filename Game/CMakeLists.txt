# Game /
# CMakeList.txt

cmake_minimum_required(	VERSION 	3.23)

link_directories(					# Dependencies
									# copied from `extlibs/libs-msvc`
									${CMAKE_CURRENT_LIST_DIR}/lib
)

add_custom_target(		copy_assets	# Visual Studio Generator from CMake [-G]
									# Copy Fonts/
									COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Fonts
									${CMAKE_CURRENT_BINARY_DIR}/Fonts

									# Copy Textures/
									COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Textures
									${CMAKE_CURRENT_BINARY_DIR}/Textures

									# Copy Resources/
									COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Resources
									${CMAKE_CURRENT_BINARY_DIR}/Resources

									# CMake Project Generated from Visual Studio [Open Visual Studio Here]
									# Copy Fonts/
									COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Fonts
									$<TARGET_FILE_DIR:Game>/Fonts

									# Copy Textures/
									COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Textures
									$<TARGET_FILE_DIR:Game>/Textures

									# Copy Resources/
									COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Resources
									$<TARGET_FILE_DIR:Game>/Resources
)

									
add_executable (		Game		# Game Executable
									"pch.cpp"
									"pch.h"
									"Main.cpp"
									"Game.cpp"
									"Game.h"
									"Window.cpp"
									"Window.h"
									"EventManager.cpp"
									"EventManager.h"
									"BaseState.h"
									"SharedContext.h"
									"StateManager.cpp"
									"StateManager.h"
									"State_Game.cpp"
									"State_Game.h"
									"State_Intro.cpp"
									"State_Intro.h"
									"State_Paused.cpp"
									"State_Paused.h"
									"State_MainMenu.cpp"
									"State_MainMenu.h"
)

add_dependencies(		Game		copy_assets)

set_property(			TARGET 		Game
						PROPERTY 	CXX_STANDARD 20
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

# TODO: Add tests and install targets if needed.