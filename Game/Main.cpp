#include "pch.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	Mac::Game game;
	while (!game.GetWindow()->IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}

	std::cin.get();
}