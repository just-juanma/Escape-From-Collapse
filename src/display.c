#include "gbl.h"

/// @brief option menu display (in the console)
/// @param registeredList list of registered players
void menuDisplay(player_t **registeredList)
{
    bool IA = false, end = false, allowed = true;
    uint16_t i, j, turn = 0, boardSize = 0, **board = NULL;
    uint8_t option = 0, movement = 0;
    size_t nLogs = 0, nInGame = 0, nRegisters = filePlayersCount();
    player_t *loggedInList = NULL, *inGameList = NULL, *foo = NULL;
    loggedInList = calloc(1, sizeof(player_t));
    foo = calloc(1, sizeof(player_t));
    printf("Welcome to Escape From the Collapse\n");
    sleep();
    while (option != 7)
    {
        inGameList = NULL;
        allowed = true;
        system("cls");
        printf("Please, select an option:\n");
        printf("1. Login\n2. Register\n3. Play\n4. How to play\n5. Stats\n6. Credits\n7. Exit\n");
        scanf("%hhu", &option);
        switch (option)
        {
        case 1:
            system("cls");
            cleanInput();
            printf("Enter your username: ");
            scanf("%[^\n]", foo->username);
            cleanInput();
            printf("Enter your password: ");
            scanf("%[^\n]", foo->password);
            if (!loginPlayer(*registeredList, &loggedInList, *foo, &nLogs, nRegisters))
            {
                system("cls");
                printf("There was an error loggin in\nIt may be:\n");
                printf("- You exceeded user name or password character limit\n");
                printf("- Your age is not valid\n");
                printf("- Your user has been already logged in\n");
            }
            cleanInput();
            sleep();
            break;
        case 2:
            cleanInput();
            system("cls");
            printf("Enter a username: ");
            scanf("%[^\n]", foo->username);
            cleanInput();
            printf("Enter a password: ");
            scanf("%[^\n]", foo->password);
            printf("Enter your age: ");
            scanf("%hu", &foo->age);
            foo->wins = 0;
            foo->wins = 0;
            if (!registerPlayer(registeredList, &loggedInList, *foo, &nLogs, &nRegisters))
            {
                system("cls");
                printf("There was an error registering in\nIt may be:\n");
                printf("- You are already logged in\n");
                printf("- You have already been registered\n");
            }
            else
            {
                fileSaving(nRegisters, *registeredList);
            }
            cleanInput();
            sleep();
            break;
        case 3:
            IA = false;
            end = false;
            nInGame = 0;
            system("cls");
            printf("How many players would you like to play with?\n");
            scanf("%d", &nInGame);
            inGameList = calloc(nInGame, sizeof(player_t));
            if (!inGameList)
            {
                system("cls");
                printf("There was an error generating in game list\nLeaving the game...");
                exit(EXIT_FAILURE);
            }
            foo = realloc(foo, nInGame * sizeof(player_t));
            for (i = 0; i < nInGame; i++)
            {
                printf("Enter the username of player %hu\n", i + 1);
                scanf("%s", foo[i].username);
            }
            cleanInput();
            if (!playersAbleToPlay(&IA, loggedInList, &inGameList, foo, nLogs, &nInGame))
            {
                system("cls");
                printf("There was an error selecting the user to play\n");
                allowed = false;
                sleep();
            }
            if (allowed)
            {
                turn = rand() % (uint16_t)nInGame;
                board = generateBoard(&boardSize);
                boardPlayerSet(nInGame, boardSize, board, inGameList);
                while (!end)
                {
                    movement = 0;
                    boardPrinting(nInGame, boardSize, board, inGameList);
                    if ((IA && turn == 0) || !IA)
                    {
                        printf("%s: select a movement:\n1 - UP\t2 - LEFT\t3 - RIGHT\t4 - DOWN\t5 - SURRENDER\n", inGameList[turn].username);
                        scanf("%hhu", &movement);
                        while (!playerMovement(boardSize, movement, board, &inGameList[turn]))
                        {
                            printf("You cannot move there\n");
                            cleanInput();
                            sleep();
                            printf("%s: select a movement:\n1 - UP\t2 - LEFT\t3 - RIGHT\t4 - DOWN\t5 - SURRENDER\n", inGameList[turn].username);
                            scanf("%hhu", &movement);
                        }
                        if (movement == SURRENDER)
                        {
                            surrender(nInGame, *registeredList, inGameList[turn]);
                            printf("%s has surrendered\n", inGameList[turn].username);
                            end = true;
                            cleanInput();
                            sleep();
                        }
                    }
                    else
                    {
                        while (!playerMovement(boardSize, ++movement, board, &inGameList[turn]))
                        {
                            if (movement == SURRENDER)
                            {
                                surrender(nInGame, *registeredList, inGameList[turn]);
                                printf("%s has surrendered\n", inGameList[turn].username);
                                end = true;
                                break;
                                cleanInput();
                                sleep();
                            }
                        }
                    }
                    if (reviewMatch(nInGame, boardSize, inGameList, *registeredList))
                    {
                        boardPrinting(nInGame, boardSize, board, inGameList);
                        printf("%s has won\n", inGameList[turn].username);
                        end = true;
                        cleanInput();
                        sleep();
                    }
                    if(!collapse(boardSize, board))
                    {
                        printf("No more positions on the board can be collapsed, ending the game...\n");
                        cleanInput();
                        sleep();
                        break;
                    }

                    turn = (turn + 1) % nInGame;
                }
                fileSaving(nRegisters, *registeredList);
                for(i = 0; i < boardSize; i++)
                {
                    board[i] = NULL;
                    free(board[i]); 
                }
                board = NULL;
                free(board);
            }
            break;
        case 4:
            printf("A board is generated, and the objective is to reach the opposite side of it before your opponents. However, every turn a square collapses (you can not access) randomly. You must plan a strategy in each game and be lucky with the collapses to win\n");
            sleep();
            break;
        case 5:
            cleanInput();
            if (!nLogs)
            {
                printf("You must log in with the user before accessing their statistics\n");
            }
            else
            {
                for (i = 0; i < nRegisters; i++)
                {
                    for (j = 0; j < nLogs; j++)
                    {
                        if (strcmp((*registeredList)[i].username, loggedInList[j].username) == 0)
                        {
                            printf("Username: %s Wins: %hu Loses: %hu Win Rate: ", (*registeredList)[i].username, (*registeredList)[i].wins, (*registeredList)[i].losses);
                            if ((*registeredList)[i].wins)
                            {
                                printf("%.2f\n", (float)(((*registeredList)[i].wins) * 100 / ((*registeredList)[i].wins + (*registeredList)[i].losses)));
                            }
                            else
                            {
                                printf("0\n");
                            }
                        }
                    }
                }
            }
            sleep();
            break;
        }
    }
    free(foo);
    free(loggedInList);
}

void boardPrinting(size_t nInGame, size_t boardSize, uint16_t **board, player_t *inGameList)
{
    system("cls");
    uint8_t i, j, k;
    for (i = 0; i < boardSize; i++)
    {
        printf("\n");
        for (j = 0; j < boardSize; j++)
        {
            if (board[i][j] == COLLAPSED)
            {
                printf(YELLOW "%c %c %c", P_ROW, P_COLLAPSED, P_ROW);
                printf(RESET);
            }
            else if (board[i][j] == FILLED)
            {
                for (k = 0; k < nInGame; k++)
                {
                    if (inGameList[k].coords.x == i &&
                        inGameList[k].coords.y == j)
                    {
                        switch (k)
                        {
                        case 0:
                            printf(MAGENTA "%c 1 %c", P_ROW, P_ROW);
                            printf(RESET);
                            break;
                        case 1:
                            printf(BLUE "%c 2 %c", P_ROW, P_ROW);
                            printf(RESET);
                            break;
                        case 2:
                            printf(CYAN "%c 3 %c", P_ROW, P_ROW);
                            printf(RESET);
                            break;
                        case 3:
                            printf(RED "%c 4 %c", P_ROW, P_ROW);
                            printf(RESET);
                            break;
                        }
                        break;
                    }
                }
            }
            else
            {
                printf("%c O %c", P_ROW, P_ROW);
            }
        }
    }
    printf("\n");
}