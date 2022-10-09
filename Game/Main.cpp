#include <time.h>

#include "Game.h"

int main()
{

    srand(time(0));
    std::cout << "Space Shooter: Initialized!" << std::endl;

    Mac::Game game;

    game.Run();

    return 0;
}