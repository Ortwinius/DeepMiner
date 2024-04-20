#include <iostream>

#include "game.h"

int main()
{
    // init game
    Game game;

    while (game.isRunning())
    {
        game.handleInput();
        game.update();
        game.render();
    }

    return 0;
}

