#include "pch.h"
#include "Game.h"
int main()
 {
    srand(static_cast<unsigned int>(time(nullptr)));
    //Creating Game Object
    Game game; 

    //Game loop
    game.run();
}


