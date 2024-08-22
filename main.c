#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define base -1
#define startPoint 0
#define numPlayers 4
#define Borad_size 51  // player pieces
#define greenHome 0000 // please assign value

typedef struct
{
    int piecesCaptured;
    int piecesPosition;
    int startgame;
    int piecesDirection;
    short pastHomeHowTimes;
    short pastpiecesDirection;

} Pieces;
// player area
typedef struct Player
{
    Pieces pieces[4]; // make 4 for pieces for one player
    char playercolor;
    int startGamePieces;
    short playerPiecesposition[4];

} Player;
typedef struct Borad
{

    int piecesNum;
    short piecesName;
    short piecesBlock;
    short mysteryCell;

} Borad;

// Call random numbers
int roll()
{
    return (rand() % 6) + 1;
}
// coin tos
int coinTos()
{
    return (rand() % 2);
}

// functions
void playermove();
int playerstart();
void playerInstall();
void greenplayer();
void yellowPlayer();
void redPlayer();
void bluePlayer();
void playerAiCall();
void boradconst();
short capturedBlock();
void checkplayer(Player *player, Borad *borad, int *position);
int countAllyPiecesAtPosition(int position, int currentPlayer, int (*pieces)[4][4], int *(allayPieces)[3], int *piecesNum);

void printPlayers(Player *player)
{
    for (int i = 0; i < numPlayers; i++)
    {
        printf("Player %d (Color: %c):\n", i + 1, player[i].playercolor);
        for (int j = 0; j < 4; j++)
        {
            printf("  Piece %d: Position = %d, StartGame = %d\n",
                   j + 1, player[i].pieces[j].piecesPosition, player[i].pieces[j].startgame);
        }
    }
}

int main()
{
    srand(time(NULL));
    // install player
    Player player[numPlayers];
    playerInstall(player);
    // make variable for startPlayer
    int startPlayer = -1;
    // install borad

    Borad borad[Borad_size];
    for (int i = 0; i < Borad_size; i++)
    {
        borad[i].piecesNum = 0;
    }
    playerstart(&startPlayer);
    printf("%d\n", startPlayer);
    // export to header.h (player play method)
    switch (startPlayer)
    {
    case 0:
        player[0].playercolor = 'R';
        player[1].playercolor = 'G';
        player[2].playercolor = 'Y';
        player[3].playercolor = 'B';
        break;
    case 1:
        player[0].playercolor = 'G';
        player[1].playercolor = 'Y';
        player[2].playercolor = 'B';
        player[3].playercolor = 'R';
        break;
    case 2:
        player[0].playercolor = 'Y';
        player[1].playercolor = 'B';
        player[2].playercolor = 'R';
        player[3].playercolor = 'G';
        break;
    case 3:
        player[0].playercolor = 'B';
        player[1].playercolor = 'R';
        player[2].playercolor = 'G';
        player[3].playercolor = 'Y';
        break;

    default:
        break;
    }
    //

    printPlayers(player);
}
int playerstart(int *startPlayer)
{

    int tie = 1;
    while (tie)
    {
        tie = 0;
        int a[4];
        for (int i = 0; i < numPlayers; i++)
        {
            int rollNum = roll();
            a[i] = rollNum;
        }
        *startPlayer = 0;
        // shrot this
        if (a[1] < a[0] && a[2] < a[0] && a[3] < a[0])
        {
            *startPlayer = 0;
            tie = 0;
        }
        if (a[0] < a[1] && a[2] < a[1] && a[3] < a[1])
        {
            tie = 0;
            *startPlayer = 1;
        }
        if (a[0] < a[2] && a[1] < a[2] && a[3] < a[2])
        {
            tie = 0;
            *startPlayer = 2;
        }
        if (a[0] < a[3] && a[2] < a[3] && a[1] < a[3])
        {
            tie = 0;
            *startPlayer = 3;
        }
    }
}
void playerInstall(Player *player)
{
    // give name for each player
    player[0].playercolor = 'R';
    player[1].playercolor = 'G';
    player[2].playercolor = 'Y';
    player[3].playercolor = 'B';
    for (int i = 0; i < numPlayers; i++)
    {
        for (int j = 0; j < numPlayers; j++)
        {
            player[i].pieces[j].piecesPosition = base;
            player[i].pieces[j].startgame = -1;
            player[i].pieces[j].piecesCaptured = 0;
        }
    }
}
// behewire of board

void boradconst(Player *player, Borad *borad)
{
    int playerNum = 0;
    int rollNum = 0;
    int piecesNum = 0;
    int picesToHome = 0; // can move pices to home
    int playerTime = 0;
    int pieces[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    /*
    player1    pieces[0][0] = 0  pieces[0][1] = 0  pieces[0][2] = 0  pieces[0][3] = 0
    player2    pieces[1][0] = 0  pieces[1][1] = 0  pieces[1][2] = 0  pieces[1][3] = 0
    player3    pieces[2][0] = 0  pieces[2][1] = 0  pieces[2][2] = 0  pieces[2][3] = 0
    player4    pieces[3][0] = 0  pieces[3][1] = 0  pieces[3][2] = 0  pieces[3][3] = 0
    */

    while (1)
    {

        // role dice
        rollNum = roll();

        // stay behind of players and borad (go around like circule)
    }
}
void playermove(int *playerNum, int *piecesNum, int rollNum, int *picesToHome, int pieces[4][4])
{
    // in this function only do move pieces and cut enmy pieces and go to mystrey cell
    Borad *borad;
    Player *player = &player[*playerNum];
    int currentPlayerPiecesPosition = player->pieces[*piecesNum].piecesPosition;

    int enemyPlayer = 0;

    while (rollNum == 0)
    {
        int enemyPieces[3] = {0, 0, 0};
        int allayPieces[3] = {0, 0, 0};
        // give picecs to X location from base

        if (*picesToHome == 1)
        {
            player->pieces[*piecesNum].piecesPosition = base;
            player->pieces[*piecesNum].startgame == 1;
            player->pieces[*piecesNum].piecesCaptured = 0;
            player->pieces[*piecesNum].pastHomeHowTimes = 0;
            player->pieces[*piecesNum].pastpiecesDirection = 0;

            int directionOfPieces = coinTos();
            if (directionOfPieces == 0)
            {
                player->pieces[*piecesNum].piecesDirection = 1;
                // print he pieces start game and his direction is colckwise
            }
            else if (directionOfPieces == 1)
            {
                player->pieces[*piecesNum].piecesDirection = 2;
                // print he pieces start game and his direction is anti clockwise
            }
            rollNum == 0;
        }

        // clockwise pieces go
        if (player->pieces[*piecesNum].piecesDirection == 1 && player->pieces[*piecesNum].startgame == 1)
        {

            int previousCurrentPiecesPosition = player->pieces[*piecesNum].piecesPosition;
            int newCurrentPiecesPosition = player->pieces[*piecesNum].piecesPosition + 1;
            int previousPlayerpieces = countAllyPiecesAtPosition(previousCurrentPiecesPosition, *playerNum, pieces, allayPieces, *piecesNum);
            int newPositionEnemyPlayerPieces = countEnemyPiecesAtPosition(newCurrentPiecesPosition, *playerNum, &enemyPlayer, pieces, enemyPieces);
            int newPositionAllayPlayerPieces = countAllyPiecesAtPosition(newCurrentPiecesPosition, *playerNum, pieces, allayPieces, *piecesNum);
            if (previousPlayerpieces == 0)
            {
                if (newPositionEnemyPlayerPieces == 0)
                {
                    printf("%c pieces %d go to %d but he can't go next position becacuse it block by enemy %c player  %d pieces\n", player->playercolor, *piecesNum, previousCurrentPiecesPosition, player[enemyPlayer].playercolor, enemyPieces[0]);
                    rollNum = 0;
                    player->pieces[*piecesNum].piecesPosition--;
                    pieces[*playerNum][*piecesNum] = player->pieces[*piecesNum].piecesPosition;
                }
                if (newPositionEnemyPlayerPieces == 1)
                {
                    printf("%c pieces %d go to %d but he can't go next position becacuse it block by enemy %c player block->(%d pieces and %d pieces)\n", player->playercolor, *piecesNum, previousCurrentPiecesPosition, enemyPieces[0], player[enemyPlayer].playercolor, enemyPieces[1]);
                    rollNum = 0;
                    player->pieces[*piecesNum].piecesPosition--;
                    pieces[*playerNum][*piecesNum] = player->pieces[*piecesNum].piecesPosition;
                }
                if (newPositionEnemyPlayerPieces == 2)
                {
                    printf("%c pieces %d go to %d but he can't go next position becacuse it block by enemy %c player block->(%d pieces and %d pieces and %d pieces)\n", player->playercolor, *piecesNum, previousCurrentPiecesPosition, player[enemyPlayer].playercolor, enemyPieces[0], enemyPieces[1], enemyPieces[2]);
                    rollNum = 0;
                    player->pieces[*piecesNum].piecesPosition--;
                    pieces[*playerNum][*piecesNum] = player->pieces[*piecesNum].piecesPosition;
                }

                if (*picesToHome == 2 && rollNum == 1 && newPositionAllayPlayerPieces == 0)
                {
                    int cureentPiecesDirection = player->pieces[*piecesNum].piecesDirection;
                    int newPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                    blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection, 0, *piecesNum, allayPieces);
                    printf("%c pieces %d go to %d make a block with %d pieces\n", player->playercolor, *piecesNum, newCurrentPiecesPosition, allayPieces[0]);
                    rollNum = 0;
                    pieces[*playerNum][*piecesNum] = player->pieces[*piecesNum].piecesPosition;
                }
                if (*picesToHome == 2 && rollNum == 1 && newPositionAllayPlayerPieces == 1)
                {
                    int cureentPiecesDirection = player->pieces[*piecesNum].piecesDirection;
                    int newPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                    int newSecondDirection = player->pieces[allayPieces[1]].piecesDirection;
                    blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection, newSecondDirection, *piecesNum, allayPieces);

                    printf("%c pieces %d go to %d make a super bolck with %d pieces and %d pieces\n", player->playercolor, *piecesNum, newCurrentPiecesPosition, allayPieces[0], allayPieces[1]);
                    rollNum = 0;
                    pieces[*playerNum][*piecesNum] = player->pieces[*piecesNum].piecesPosition;
                }
                if (*picesToHome == 2 && rollNum == 1 && newPositionAllayPlayerPieces == 2)
                {
                    printf("%c pieces %d go to %d but he can't go next position becacuse it block by allay block %d pieces , %d pieces and %d pieces\n", player->playercolor, *piecesNum, previousCurrentPiecesPosition, allayPieces[0], allayPieces[1], allayPieces[2]);
                    rollNum = 0;
                    player->pieces[*piecesNum].piecesPosition--;
                    pieces[*playerNum][*piecesNum] = player->pieces[*piecesNum].piecesPosition;
                }
                if (*picesToHome == 4 && rollNum == 1 && newPositionEnemyPlayerPieces == 1)
                {
                    printf("%c pieces %d capture %c player %d pieces \n", player->playercolor, *piecesNum, player[enemyPlayer].playercolor, enemyPieces[0]);
                    rollNum = 0;
                    pieces[*playerNum][*piecesNum] = player->pieces[*piecesNum].piecesPosition;
                }
            }
            if (previousPlayerpieces == 1)
            {
                if
            }
        }
    }
}

void greenplayer(Player *player, Borad *borad, int *rollNum, int *piecesToHome, int *piecesNum)

{

    if (*rollNum == 6)
    {
        for (int i = 0; i < numPlayers; i++)
        {
            if (player->pieces[i].piecesPosition == base) // not home in base

            {
                *piecesNum = i;
                *piecesToHome = 1;
            }
        }
    }

    for (int i = 0; i < numPlayers; i++)
    {
        player->playerPiecesposition[i] = player->pieces[i].piecesPosition;

        if (player[player->playerPiecesposition[i]].pieces[i].startgame == 1)

        {
            int newPlayerPiesesPosition = player->playerPiecesposition[i] + *rollNum;
            // Check for existing block or potential block formation
            for (int j = 0; j < numPlayers; j++)
            {
                if (i != j && newPlayerPiesesPosition == player[j].pieces[j].piecesPosition)
                {
                    if (borad[player->playerPiecesposition[i]].piecesNum == 4 && borad[newPlayerPiesesPosition].piecesNum == 4)
                    {
                        // he create block
                        *piecesNum = i;
                        *piecesToHome = 2;
                    }
                    if (borad[player->playerPiecesposition[i]].piecesNum == 8 && borad[newPlayerPiesesPosition].piecesNum == 4)
                    {
                        // he create super block
                        *piecesNum = 2;
                    }
                    if (borad[player->playerPiecesposition[i]].piecesNum == 4 && borad[newPlayerPiesesPosition].piecesNum == 8)
                    {
                        // he create superblock
                        *piecesNum = 2;
                    }
                }
            }
        }
    }
}

int countEnemyPiecesAtPosition(int position, int currentPlayer, int *enemyIndex, int (*pieces)[4][4], int (*enemyPieces)[3])
{
    int count = 0;
    int firstPlayerIndex = -1;

    // Iterate over all players and their pieces
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (pieces[i][j] == position)
            {
                if (firstPlayerIndex == -1)
                {
                    firstPlayerIndex = i; // Set the first player index who has a piece at this position
                }
                else if (firstPlayerIndex != i)
                {
                    *enemyIndex = i; // If a different player is found, set the enemy index
                    if (*enemyPieces[0] == 0)
                    {
                        *enemyPieces[0] = j;
                        count++;
                    }
                    else if (*enemyPieces[1] == 0 && *enemyPieces[0] > 0)
                    {
                        *enemyPieces[1] = j;
                        count++;
                    }
                    else if (*enemyPieces[2] && *enemyPieces[1] > 0 && *enemyPieces[0] > 0)
                    {
                        *enemyPieces[2] = j;
                        count++;
                    }
                }
            }
        }
    }

    // Return the count (which will be 1, 2, or 3)
    if (count == 3 || position == base)
    {
        return 0; // Return 0 if four pieces are in the same position, or the position is 0
    }

    return count;
}

int countAllyPiecesAtPosition(int position, int currentPlayer, int (*pieces)[4][4], int *(allayPieces)[3], int *piecesNum)
{
    int count = 0;
    // Iterate over all players and their pieces
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (pieces[i][j] == position && i == currentPlayer)
            {
                if (allayPieces[0] == 0 && j != piecesNum)
                {
                    allayPieces[0] = j;
                    count++;
                }
                else if (allayPieces[0] > 0 && allayPieces[1] == 0 && j != piecesNum)
                {
                    allayPieces[1] = j;
                    count++;
                }
                else if (allayPieces[1] > 0 && allayPieces[2] == 0 && allayPieces[0] > 0 && j != piecesNum)

                {
                    allayPieces[2] = j;
                    count++;
                }
            }
        }
    }
    return count;
    if (count == 3 || position == base)
    {
        return 0; // Return 0 if four pieces are in the same position, or the position is 0
    }

    return count;
}
void blockDirectionChecker(Player *player, Borad *borad, int cureentPiecesDirection, int newPiecesDirection, int newSecondPiecesDirection, int piecesNum, int *allayPieces)
{
    if (cureentPiecesDirection != newPiecesDirection && newSecondPiecesDirection == 0)
    {
        if (cureentPiecesDirection == 2)
        {
            if (player->pieces[piecesNum].pastHomeHowTimes == 1)
            {
                int currentPiecesPosition = Borad_size - greenHome;
                currentPiecesPosition += player->pieces[piecesNum].piecesPosition;
                int newPiecesPosition = Borad_size - player->pieces[allayPieces[0]].piecesPosition;
                if (newPiecesPosition > currentPiecesPosition)
                {
                    player->pieces[piecesNum].piecesDirection = 1;
                    player->pieces[piecesNum].pastpiecesDirection = 2;
                }
                else
                {
                    player->pieces[allayPieces[0]].piecesDirection = 2;
                    player->pieces[allayPieces[0]].pastpiecesDirection = 1;
                }
            }
        }
        if (newPiecesDirection == 2)
        {
            if (player->pieces[allayPieces[0]].pastHomeHowTimes == 1)
            {
                int newPiecesPosition = Borad_size - greenHome;
                newPiecesPosition += player->pieces[piecesNum].piecesPosition;
                int currentPiecesPosition = Borad_size - player->pieces[allayPieces[0]].piecesPosition;
                if (currentPiecesPosition > newPiecesPosition)
                {
                    player->pieces[allayPieces[0]].piecesDirection = 1;
                    player->pieces[allayPieces[0]].pastpiecesDirection = 2;
                }
                else
                {
                    player->pieces[piecesNum].piecesDirection = 2;
                    player->pieces[piecesNum].pastpiecesDirection = 1;
                }
            }
        }
    }
}
