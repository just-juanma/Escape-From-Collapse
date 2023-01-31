#include "gbl.h"

/// @brief checks if the players are able to play
/// @param IA detects if the IA is playing, and change the value to true (or false)
/// @param loggedList list of loggged in players -> checks that players are logged in before playing
/// @param inGameList list of players in game -> it will update the list in case players are able to play
/// @param playersToPlay list of possible players
/// @param nLogs number of logged in players
/// @param nInGame number of players in game
/// @return if the players are able to play, or not
bool playersAbleToPlay(bool *IA, player_t *loggedList, player_t **inGameList, player_t *playersToPlay, size_t nLogs, size_t *nInGame)
{
    uint16_t i, j;
    uint16_t partialNInGame = 0; // each time a player is added to the list, this counter increases by 1
    for (i = 0; i < nLogs; i++)
    {
        for (j = 0; j < *nInGame; j++)
        {
            if (strcmp(playersToPlay[j].username, loggedList[i].username) == 0)
            {
                *inGameList[partialNInGame++] = playersToPlay[j];
            }
        }
    }

    //! check if there are players logged in (the same number of players added to the list in game is the same as nInGame)
    if (partialNInGame != *nInGame)
        return false;

    // IA generation
    if (*nInGame == 1)
    {
        *IA = true;
        player_t *tempIA = calloc(1, sizeof(player_t));
        strcpy((*tempIA).username, "IA");
        *inGameList = realloc(*inGameList, (*nInGame)++ * sizeof(player_t));
        (*inGameList)[partialNInGame] = *tempIA;
    }
    return true;
}

/// @brief game board generation
/// @param boardSize size of the board (boardSize x boardSize)
/// @return game board
uint16_t **generateBoard(uint16_t *boardSize)
{
    uint8_t i, j;
    boardSize = rand() % 20 + 6;                              // random between 6 and 25
    uint16_t **board = calloc(*boardSize, sizeof(uint16_t *)); // row (or column) dinamic memory request
    for (i = 0; i < *boardSize; i++)                           // for each column (or row), dinamic memory request (see line 55)
    {
        board[i] = calloc(*boardSize, sizeof(uint16_t));
        for (j = 0; j < *boardSize; j++)
        {
            board[i][j] = FREE;
        }
    }
    return board;
}

/// @brief distribution of players on the board
/// @param nInGame number of players in game -> to be able to set them in an order
/// @param boardSize size of the board (boardSize x boardSize) -> to be able to set some players over the board boundary
/// @param board game board
/// @param inGameList list of players in game
void boardPlayerSet(size_t nInGame, uint16_t boardSize, uint16_t **board, player_t *inGameList)
{
    uint16_t i;
    for (i = 0; i < nInGame; i++)
    {
        // different positions depending on the number of players (i)
        switch (i)
        {
        case 0:
            inGameList[i].coords.x = 0;
            inGameList[i].coords.y = 0;
            board[i][i] = FILLED;
            break;
        case 1:
            inGameList[i].coords.x = boardSize - 1;
            inGameList[i].coords.y = boardSize - 1;
            board[boardSize - 1][boardSize - 1] = FILLED;
            break;
        case 2:
            inGameList[i].coords.x = 0;
            inGameList[i].coords.y = boardSize - 1;
            board[0][boardSize - 1] = FILLED;
            break;
        case 3:
            inGameList[i].coords.x = boardSize - 1;
            inGameList[i].coords.y = 0;
            board[boardSize - 1][0] = FILLED;
            break;
        }
    }
}

/// @brief checks the player's movement, each time it is attempted to execute
/// @param boardSize size of the board (boardSize x boardSize) -> the player does not exceed the board size
/// @param movement player movement
/// @param board game board
/// @param player player attempting to move
/// @return if the player is able to move, or not
bool movementReview(uint16_t boardSize, uint8_t movement, uint16_t **board, player_t player)
{
    if (movement < 1 || movement > 5)
    {
        return false;
    }
    switch (movement)
    {
    case UP:
        if (player.coords.x - 1 >= 0 &&
            board[player.coords.x - 1][player.coords.y] == FREE)
        {
            return true;
        }
        break;
    case RIGHT:
        if (player.coords.y + 1 < boardSize &&
            board[player.coords.x][player.coords.y + 1] == FREE)
        {
            return true;
        }
        break;
    case LEFT:
        if (player.coords.y - 1 >= 0 &&
            board[player.coords.x][player.coords.y - 1] == FREE)
        {
            return true;
        }
        break;
    case DOWN:
        if (player.coords.x + 1 < boardSize &&
            board[player.coords.x + 1][player.coords.y] == FREE)
        {
            return true;
        }
        break;
    case SURRENDER:
        return true;
    }
    return false;
}

/// @brief player's movement (same as the board) once is permitted
/// @param boardSize board size to check player's movement
/// @param movement player's movement
/// @param board board to free up certain boxes
/// @param player player who wants to execute the move
/// @return if the player is able to move, or not
bool playerMovement(uint16_t boardSize, uint8_t movement, uint16_t **board, player_t *player)
{
    // check that the movement is valid
    if (!movementReview(boardSize, movement, board, *player))
        return false;
    // the player's current position within the board becomes free
    board[player->coords.x][player->coords.y] = FREE;
    switch (movement)
    {
    case UP:
        // the board and the player's coordinates are occupied
        board[player->coords.x - 1][player->coords.y] = FILLED;
        player->coords.x = player->coords.x - 1;
        break;
    case RIGHT:
        board[player->coords.x][player->coords.y + 1] = FILLED;
        player->coords.y = player->coords.y + 1;
        break;
    case DOWN:
        board[player->coords.x + 1][player->coords.y] = FILLED;
        player->coords.x = player->coords.x + 1;
        break;
    case LEFT:
        board[player->coords.x][player->coords.y - 1] = FILLED;
        player->coords.y = player->coords.y - 1;
        break;
    case SURRENDER:
        break;
    }
    return true;
}

/// @brief random collapse at each turn
/// @param boardSize size of the board -> to randomize the position
/// @param board game board
bool collapse(uint16_t boardSize, uint16_t **board)
{
    uint16_t i, j; 
    uint16_t x = rand() % boardSize, y = rand() % boardSize; // randoms between 0 and boardSize var
    for (i = 0; i < boardSize; i++)
    {
        for (j = 0; j < boardSize; j++)
        {
            // check for FREE posisiton
            if (board[i][j] == FREE)
            {
                while (board[x][y] != FREE) // if the position is FILLED or has already been COLLAPSED:
                {
                    x = rand() % boardSize;
                    y = rand() % boardSize;
                }
                board[x][y] = COLLAPSED;
                return true;
            }
        }
    }
    // if no FREE position
    return false;
}

/// @brief surrender system in case any player chooses to do
/// @param nInGame number of players in game
/// @param registeredList list of registered players -> in order to register it in the file
/// @param surrenderPlayer player who surrendered
void surrender(size_t nInGame, player_t *registeredList, player_t surrenderPlayer)
{
    uint16_t i;
    for (i = 0; i < nInGame; i++)
    {
        if (strcmp(surrenderPlayer.username, registeredList[i].username) == 0)
        {
            registeredList[i].losses++;
        }
        else
        {
            registeredList[i].wins++;
        }
    }
}

/// @brief victory system in case any player wins
/// @param nInGame number of players in game
/// @param registeredList list of registered players -> in order to register it in the file
/// @param winnerPlayer player who won
void win(size_t nInGame, player_t *registeredList, player_t winnerPlayer)
{
    uint16_t i;
    for (i = 0; i < nInGame; i++)
    {
        if (strcmp(winnerPlayer.username, registeredList[i].username) == 0)
        {
            registeredList[i].wins++;
        }
        else
        {
            registeredList[i].losses++;
        }
    }
}


/// @brief at the end of each turn, a check is made to see if there is a winner. If there is a winner, the winner is announced
/// @param nInGame number of players in game
/// @param boardSize size of the board -> to verify if certain players have reached the limit of the board
/// @param inGameList list of players in game
/// @param registeredList list of registered players -> in order to register it in the file
/// @return if the game is over, or not
bool reviewMatch(size_t nInGame, size_t boardSize, player_t *inGameList, player_t *registeredList)
{
    uint16_t i;
    for (i = 0; i < nInGame; i++)
    {
        switch (i)
        {
        case 0:
            if (inGameList[i].coords.x == boardSize - 1)
            {
                win(nInGame, registeredList, inGameList[i]);
                return true;
            }
            break;
        case 1:
            if (inGameList[i].coords.x == 0)
            {
                win(nInGame, registeredList, inGameList[i]);
                return true;
            }
            break;
        case 2:
            if (inGameList[i].coords.x == boardSize - 1)
            {
                win(nInGame, registeredList, inGameList[i]);
                return true;
            }
            break;
        case 3:
            if (inGameList[i].coords.x == 0)
            {
                win(nInGame, registeredList, inGameList[i]);
                return true;
            }
            break;
        }
    }
    return false;
}