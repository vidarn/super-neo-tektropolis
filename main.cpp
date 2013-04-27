#include "game.hpp"
#include "common.hpp"

int
main(int argc, char **argv)
{
    Game game("I forgot to give this window a title", 800, 550);
    return game.run();
}
