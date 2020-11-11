
#include <raylib.h>

#include "game.h"

int main(int argc, char* argv[])
{
    int screenWidth = 640;
    int screenHeight = 800;

    //InitWindow(screenWidth, screenHeight, "Minestorm - Remi");

    Game game(screenWidth, screenHeight);

    game.gameLoop();

    return 0;
}