#include "gbl.h"

/// @brief player login system
/// @param registeredList list of registered players -> to check that the player is previously registered
/// @param loggedList list of loggged in players -> to add the player to the list (in case the player is able to login)
/// @param playerToLog player to log in
/// @param nLogs number of logged in players
/// @param nRegisters number of registered players
/// @return true if the player could log in, false if not
bool loginPlayer(player_t *registeredList, player_t **loggedList, player_t playerToLog, size_t *nLogs, size_t nRegisters)
{
    uint16_t i;
    // check if the player has logged in previously:
    for (i = 0; i < *nLogs; i++)
    {
        if (strcmp(playerToLog.username, loggedList[i]->username) == 0 &&
            strcmp(playerToLog.password, loggedList[i]->password) == 0)
        {
            return false;
        }
    }

    // check if the player is in the registered list:
    if (nRegisters)
    {
        for (i = 0; i < nRegisters; i++)
        {
            if (strcmp(playerToLog.username, registeredList[i].username) == 0 &&
                strcmp(playerToLog.password, registeredList[i].password) == 0)
            {
                // player added to the list:
                *loggedList = realloc(*loggedList, ++(*nLogs) * sizeof(player_t));
                (*loggedList)[*nLogs - 1] = registeredList[i];
                return true;
            }
        }
    }
    return false;
}

/// @brief player registration system
/// @param registeredList list of registered players -> to add the player to the list (in case the player is able to register)
/// @param loggedList list of loggged in players -> once registered, the player will be automatically logged in
/// @param playerToRegister player to register
/// @param nLogs number of logged in players
/// @param nRegisters number of registered players
/// @return true if the player could register, false if not
bool registerPlayer(player_t **registeredList, player_t **loggedList, player_t playerToRegister, size_t *nLogs, size_t *nRegisters)
{
    uint16_t i;

    // check if the player was already registered:
    for (i = 0; i < *nRegisters; i++)
    {
        if (strcmp(playerToRegister.username, registeredList[i]->username) == 0)
        {
            return false;
        }
    }

    //! player added to both list:
    *loggedList = realloc(*loggedList, ++(*nLogs) * sizeof(player_t));
    *registeredList = realloc(*registeredList, ++(*nRegisters) * sizeof(player_t));
    (*registeredList)[*nRegisters - 1] = playerToRegister;
    (*loggedList)[*nLogs - 1] = playerToRegister;
    return true;
}