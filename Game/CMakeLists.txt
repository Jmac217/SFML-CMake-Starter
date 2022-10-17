# Game /
# CMakeList.txt

cmake_minimum_required(	VERSION 	3.23)

add_custom_target(		copy_assets	# Visual Studio Generator from CMake [-G]
									# Copy Media/
									COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Assets
									${CMAKE_CURRENT_BINARY_DIR}/Assets

									# CMake Project Generated from Visual Studio [Open Visual Studio Here]
									# Copy Media/
									COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Assets
									$<TARGET_FILE_DIR:Game>/Assets
)

add_executable (		Game		# Game Executable
									"Anim_Base.cpp"
									"Anim_Base.h"
									"Anim_Directional.cpp"
									"Anim_Directional.h"
									"BaseState.h"
									"Bitmask.h"
									"CMakeLists.txt"
									"Communicator.h"
									"C_Base.h"
									"C_Collidable.h"
									"C_Controller.h"
									"C_Drawable.h"
									"C_Movable.h"
									"C_Position.h"
									"C_SpriteSheet.h"
									"C_State.h"
									"DebugOverlay.h"
									"Directions.h"
									"ECS_Types.h"
									"EntityEvents.h"
									"EntityMessages.h"
									"Entity_Manager.cpp"
									"Entity_Manager.h"
									"EventManager.cpp"
									"EventManager.h"
									"Event_Queue.h"
									"Game.cpp"
									"Game.h"
									"Main.cpp"
									"Map.cpp"
									"Map.h"
									"Message.h"
									"MessageHandler.h"
									"Observer.h"
									"ResourceManager.h"
									"SharedContext.h"
									"SpriteSheet.cpp"
									"SpriteSheet.h"
									"StateManager.cpp"
									"StateManager.h"
									"State_Game.cpp"
									"State_Game.h"
									"State_GameOver.cpp"
									"State_GameOver.h"
									"State_Intro.cpp"
									"State_Intro.h"
									"State_MainMenu.cpp"
									"State_MainMenu.h"
									"State_Paused.cpp"
									"State_Paused.h"
									"System_Manager.cpp"
									"System_Manager.h"
									"S_Base.cpp"
									"S_Base.h"
									"S_Collision.cpp"
									"S_Collision.h"
									"S_Control.cpp"
									"S_Control.h"
									"S_Movement.cpp"
									"S_Movement.h"
									"S_Renderer.cpp"
									"S_Renderer.h"
									"S_SheetAnimation.cpp"
									"S_SheetAnimation.h"
									"S_State.cpp"
									"S_State.h"
									"TextureManager.h"
									"Utilities.h"
									"Window.cpp"
									"Window.h"
)

add_dependencies(		Game		copy_assets)

set_property(			TARGET 		Game
						PROPERTY 	CXX_STANDARD	20
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
									Shlwapi

									# SFML
									sfml-system
									sfml-window
									sfml-graphics
									sfml-audio
									sfml-network
)

# TODO: Add tests and install targets when needed.