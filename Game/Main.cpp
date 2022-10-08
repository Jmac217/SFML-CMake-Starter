#include "Game.h"

int main()
{
    srand(static_cast<unsigned>(time(0)));

    Mac::Game game;

    while (game.running())
    {
        // Loop
        game.update();
        game.render();
    }

    return 0;
}