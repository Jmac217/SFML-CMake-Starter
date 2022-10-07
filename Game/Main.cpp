#include "Game.h"

int main()
{
    srand(static_cast<unsigned>(time(NULL)));

    Mac::Game game;

    while(game.Running() && !game.EndGame())
    {
        game.update();

        game.render();
    }

    return 0;
}