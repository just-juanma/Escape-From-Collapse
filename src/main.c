#include "gbl.h"

int main(void)
{
    srand((uint32_t)time(NULL)); // pseudo-random numbers generator for the board size of the game
    player_t *registeredList = NULL;
    registeredList = initializePlayers();
    if (!registeredList)
        return EXIT_FAILURE;
    menuDisplay(&registeredList);
    return EXIT_SUCCESS;
}