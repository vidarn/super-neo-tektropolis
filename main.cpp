#include "game.hpp"
#include "common.hpp"

int
main(int argc, char **argv)
{
    Game game("Super Neo Tektropolis", 800, 550);
    return game.run();
}
