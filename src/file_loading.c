#include "gbl.h"

/// @brief initializes the list of players registered in the "data" file. is divided into two sections, based on whether there are players in the file (or not)
/// @return registered list of players
player_t *initializePlayers(void)
{
    player_t *tempList = NULL;
    size_t nPlayers = filePlayersCount();
    if (nPlayers) //? are there players in the file?
    {
        //? yes -> read the file
        tempList = calloc(nPlayers, sizeof(player_t));
        playerLoading(nPlayers, tempList);
    }
    else
    {
        //? no -> generate the file (there are not players to read from file)
        fileGeneration();
        tempList = calloc(1, sizeof(player_t));
    }
    return tempList;
}

/// @brief get the number of players in the "data" file from a calculation using the file pointer and the size in bytes of the struct "player_t"
/// @return number of players
size_t filePlayersCount(void)
{
    FILE *fp = NULL;
    size_t playerCount = 0;
    fp = fopen(FILE_NAME, READING_BINARY);
    if (!fp)
        return 0;
    fseek(fp, 0, SEEK_END);
    playerCount = ftell(fp) / sizeof(player_t);
    fclose(fp);
    return playerCount;
}

/// @brief loads the list of players from the "data" file, knowing that there is at least one player in it
/// @param nRegisters number of registered players
/// @param registeredList list of registered players (to be loaded via fread)
void playerLoading(size_t nRegisters, player_t *registeredList)
{
    FILE *fp = NULL;
    fp = fopen(FILE_NAME, READING_BINARY);
    fread(registeredList, sizeof(player_t), nRegisters, fp);
    fclose(fp);
}

void fileGeneration(void)
{
    FILE *fp = NULL;
    fp = fopen(FILE_NAME, WRITING_BINARY);
    fclose(fp);
}

/// @brief writes the list of registered players (after modifying it) to the "data" file
/// @param nRegisters number of registered players
/// @param registeredList list of registered players (to be loaded via fread)
void fileSaving(size_t nRegisters, player_t *registeredList)
{
    FILE *fp = NULL;
    fp = fopen(FILE_NAME, READING_WRITING_BINARY);
    fwrite(registeredList, sizeof(player_t), nRegisters, fp);
    fclose(fp);
}