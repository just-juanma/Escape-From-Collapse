#ifndef GBL_H
#define GBL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

#define FILE_NAME "data.bin"

#define READING_BINARY "rb"
#define WRITING_BINARY "wb"
#define READING_WRITING_BINARY "r+b"
        
#define RESET "\033[0m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"

#define P_ROW 179
#define P_COLLAPSED 254

typedef struct
{
    uint16_t x;
    uint16_t y;
} coordinates_t;

typedef struct
{
    char username[20];
    char password[20];
    uint16_t age;
    uint16_t wins;
    uint16_t losses;
    coordinates_t coords;
} player_t;

enum CELL_STATUS
{
    FREE,
    FILLED,
    COLLAPSED
};

enum movement
{
    UP = 1,
    LEFT,
    RIGHT,
    DOWN,
    SURRENDER
};

player_t *initializePlayers(void);
size_t filePlayersCount(void);
void playerLoading(size_t nRegisters, player_t *registeredList);
void fileGeneration(void);
void fileSaving(size_t nRegisters, player_t *registeredList);

bool loginPlayer(player_t *registeredList, player_t **loggedList, player_t forcePlayer, size_t *nLogs, size_t nRegisters);
bool registerPlayer(player_t **registeredList, player_t **loggedList, player_t forcePlayer, size_t *nLogs, size_t *nRegisters);
bool playersAbleToPlay(bool *IA, player_t *loggedList, player_t **inGameList, player_t *forcePlayers, size_t nLogs, size_t *nInGame);

uint16_t **generateBoard(uint16_t *boardSize);
void boardPlayerSet(size_t nInGame, uint16_t boardSize, uint16_t **board, player_t *inGameList);
bool playerMovement(uint16_t boardSize, uint8_t movement, uint16_t **board, player_t *player);
bool movementReview(uint16_t boardSize, uint8_t movement, uint16_t **board, player_t player);
bool collapse(uint16_t boardSize, uint16_t **board);
void surrender(size_t nInGame, player_t *registeredList, player_t surrenderPlayer); 
void win(size_t nInGame, player_t *registeredList, player_t surrenderPlayer);
bool reviewMatch(size_t nInGame, size_t boardSize, player_t *inGameList, player_t *registeredList);

inline void cleanInput(void)
{
    int foo;
    while ((foo = getchar()) != '\n')
        ;
}
inline void sleep(void)
{
    printf("Press any key to continue...\n");
    getchar();
}

void menuDisplay(player_t **registeredList);

void boardPrinting(size_t nInGame, size_t boardSize, uint16_t **board, player_t *inGameList);

#endif