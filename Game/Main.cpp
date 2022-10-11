#include "pch.h"
#include "Game.h"

int main()
{
    srand(time(0));

    std::cout << "Platformer Initialized...!\n";

    Mac::Game game;

    while (game.getWindow().isOpen())
    {
        game.update();
        game.render();
    }

    return 0;
}