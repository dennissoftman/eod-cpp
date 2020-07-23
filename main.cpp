#include "include/core.hpp"

int main()
{
    GameWindow *game = new GameWindow();
    game->init();
    return game->run();
}
