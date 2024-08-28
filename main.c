#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define base -1
#define startPoint 0
#define numPlayers 4
#define Borad_size 51  // player pieces
#define greenHome 0000 // please assign value
#define bawanaCell 9
#define KotuwaCell 27
#define PitaKotuwaCell 46

typedef struct
{
    int piecesCaptured;
    int piecesPosition;
    int startgame;
    int piecesDirection;
    short pastHomeHowTimes;
    short pastpiecesDirection;
    short piecesBlock;

} Pieces;
// player area
typedef struct Player
{
    Pieces pieces[4]; // make 4 for pieces for one player
    char playercolor;
    int startGamePieces;
    short playerPiecesposition[4];
    short piecesBlock;
    int mystryCell;

} Player;
typedef struct Borad
{

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
void piecesCaptured();
void checkplayer(Player *player, Borad *borad, int *position);
int countAllyPiecesAtPosition(int position, int currentPlayer, int (*pieces)[4][4], int *(allayPieces)[3], int *piecesNum);
void blockBreaker(Player *player,Borad *borad,int allayplayer,int pieces1,int pieces2,int pieces3);

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
        borad[i].piecesBlock = 0;
        borad[i].mysteryCell = 0;
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
    player;
    borad;
    short playerNum = 0;
    short rollNum = 0;
    short piecesNum[3] = {0,0,0};
    short howManyPiecesStart=0;
    int picesToHome = 0; 
    int howManyTimesPlay[numPlayers]={0,0,0,0};
    int checkSixTimes=0;
    
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
        if (rollNum == 6)
        {            
            playerNum;
            checkSixTimes++;
            playerCall(player,borad,playerNum,&picesToHome,rollNum,&piecesNum,pieces);


            if (checkSixTimes == 3)
            {
                if (player[playerNum].piecesBlock == 1)
                {   
                    printf("%c player roll 6 in three times so remove BLOCK in %d position and move them six times\n");

                    int array[2]={0,0,0};
                    for (short i = 0; i < 4; i++)
                    {
                        if (player[playerNum].pieces[i].piecesBlock == 1 || player[playerNum].pieces[i].piecesBlock == 2)
                        {
                            if (array[0] == 0)
                            {
                                array[0]=i;
                            }
                            else if (array[1] == 0)
                            {
                                array[1]=i;
                            }
                            else if (array[2] == 0)
                            {
                                array[2]=i;
                            }
                        }
                    }
                    playermove(&playerNum,array[0],6,0,pieces,1,&howManyPiecesStart);
                    playermove(&playerNum,array[1],6,0,pieces,1,&howManyPiecesStart);
                    playermove(&playerNum,array[2],6,0,pieces,1,&howManyPiecesStart);
                    // break down block and move them six times
                    blockBreaker(player,borad,playerNum,array[0],array[1],array[2]);
                    
                }
                playerNum++;
                playerCall(&player,&borad,playerNum,&picesToHome,rollNum,&piecesNum,pieces);
            }else{
               
                playerNum++;
                playerCall(&player,&borad,playerNum,&picesToHome,rollNum,&piecesNum,pieces);
            }

        }
        else
        {
            howManyTimesPlay[playerNum]++;
            playerNum++;
            playerCall(&player, &borad, playerNum, &picesToHome, rollNum, &piecesNum, pieces);
        }
        if (howManyTimesPlay[0] != 1 && howManyTimesPlay[0] == howManyTimesPlay[1] && howManyTimesPlay[1] == howManyTimesPlay[2] && howManyTimesPlay[2] == howManyTimesPlay[3])
        {
            if (howManyPiecesStart > 2 && (howManyTimesPlay[0] % 4) == 1)
            {
                int stop=1;
                while (stop)
                {                
                int mystryNum = roll() % 52;
                if(borad[mystryNum].mysteryCell!= 1)
                {
                borad[mystryNum].mysteryCell = 1;
                stop=0;
                }                    
                }

            }

            //print what is status of all players position 
            printPlayers(player);
        }

        playerNum%=4;
        // stay behind of players and borad (go around like circule)
    }
}
void playermove(int *playerNum, int piecesNum[2], int rollNum, int *picesToHome, int pieces[4][4],int sixTimesBlock,int howManyPiecesStart )
{
    // in this function only do move pieces and cut enmy pieces and go to mystrey cell
    Borad *borad;
    Player *player = &player[*playerNum];
    int currentPlayerPiecesPosition = player->pieces[piecesNum[0]].piecesPosition;

    int enemyPlayer = 0;

    while (rollNum==0)
    {
        int enemyPieces[3] = {0, 0, 0};
        int allayPieces[3] = {0, 0, 0};
        int piecesNum[3] = {0, 0, 0};

        // give picecs to X location from base

        if (*picesToHome == 1)
        {
            player->pieces[piecesNum[0]].piecesPosition = base;
            player->pieces[piecesNum[0]].startgame == 1;
            player->pieces[piecesNum[0]].piecesCaptured = 0;
            player->pieces[piecesNum[0]].pastHomeHowTimes = 0;
            player->pieces[piecesNum[0]].pastpiecesDirection = 0;
            howManyPiecesStart++;

            int directionOfPieces = coinTos();
            if (directionOfPieces == 0)
            {
                player->pieces[piecesNum[0]].piecesDirection = 1;
                // print he pieces start game and his direction is colckwise
            }
            else if (directionOfPieces == 1)
            {
                player->pieces[piecesNum[0]].piecesDirection = 2;
                // print he pieces start game and his direction is anti clockwise
            }
            rollNum == 0;
        }

        // clockwise pieces go
        if (player->pieces[piecesNum[0]].piecesDirection == 1 && player->pieces[piecesNum[0]].startgame == 1)
        {

            int previousCurrentPiecesPosition = player->pieces[piecesNum[0]].piecesPosition;
            int newCurrentPiecesPosition = player->pieces[piecesNum[0]].piecesPosition + 1;
            int previousPlayerpieces = sizeof(piecesNum) / sizeof(pieces[0]);
            int newPositionEnemyPlayerPieces = countEnemyPiecesAtPosition(newCurrentPiecesPosition, *playerNum, &enemyPlayer, pieces, enemyPieces);
            int newPositionAllayPlayerPieces = countAllyPiecesAtPosition(newCurrentPiecesPosition, *playerNum, pieces[0], allayPieces, piecesNum[0]);
            if (piecesNum[1] > 0)
            {
                player->pieces[piecesNum[1]].piecesPosition++;
            }
            if (piecesNum[2]>0)
            {
                player->pieces[piecesNum[2]].piecesPosition++;
            }

            // 0ne pieces
            if (previousPlayerpieces == 0 &&sixTimesBlock==0)
            {
                if (newPositionEnemyPlayerPieces == 1)
                {
                    printf("%c pieces %d go to %d but he can't go next position becacuse it block by enemy %c player block->(%d pieces and %d pieces)\n", player->playercolor, piecesNum[0], previousCurrentPiecesPosition, enemyPieces[0], player[enemyPlayer].playercolor, enemyPieces[1]);
                    rollNum = 0;
                    player->pieces[piecesNum[0]].piecesPosition--;
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                }
                if (newPositionEnemyPlayerPieces == 2)
                {
                    printf("%c pieces %d go to %d but he can't go next position becacuse it block by enemy %c player block->(%d pieces and %d pieces and %d pieces)\n", player->playercolor, piecesNum[0], previousCurrentPiecesPosition, player[enemyPlayer].playercolor, enemyPieces[0], enemyPieces[1], enemyPieces[2]);
                    rollNum = 0;
                    player->pieces[piecesNum[0]].piecesPosition--;
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                }

                if (*picesToHome == 2 && rollNum == 1 && newPositionAllayPlayerPieces == 0)
                {
                    int cureentPiecesDirection = player->pieces[*piecesNum].piecesDirection;
                    int newPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                    // block direction checker
                    blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection, 0, piecesNum[0], allayPieces);
                    // print what happend
                    printf("%c pieces %d go to %d make a block with %d pieces\n", player->playercolor, piecesNum[0], newCurrentPiecesPosition, allayPieces[0]);
                    // handle for block for future use
                    player->piecesBlock++;
                    player->pieces[piecesNum[0]].piecesBlock = 1;
                    player->pieces[allayPieces[0]].piecesBlock = 1;
                    // end while loop
                    rollNum = 0;
                    // assing  new position to pieces
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                    pieces[*playerNum][allayPieces[0]] = player->pieces[piecesNum[0]].piecesPosition;
                }
                if (*picesToHome == 2 && rollNum == 1 && newPositionAllayPlayerPieces == 1)
                {
                    int cureentPiecesDirection = player->pieces[piecesNum[0]].piecesDirection;
                    int newPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                    int newSecondDirection = player->pieces[allayPieces[1]].piecesDirection;
                    blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection, newSecondDirection, piecesNum[0], allayPieces);
                    // handle for block for future use
                    player->piecesBlock++;
                    player->pieces[piecesNum[0]].piecesBlock = 2;
                    player->pieces[allayPieces[0]].piecesBlock = 2;
                    player->pieces[allayPieces[1]].piecesBlock = 2;
                    // print what happend
                    printf("%c pieces %d go to %d make a super bolck with %d pieces and %d pieces\n", player->playercolor, piecesNum[0], newCurrentPiecesPosition, allayPieces[0], allayPieces[1]);
                    // end while loop
                    rollNum = 0;
                    // assing  new position to pieces
                    pieces[*playerNum][allayPieces[0]] = player->pieces[allayPieces[0]].piecesPosition;
                    pieces[*playerNum][allayPieces[1]] = player->pieces[allayPieces[1]].piecesPosition;
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                }
                if (*picesToHome == 2 && rollNum == 1 && newPositionAllayPlayerPieces == 2)
                {
                    printf("%c pieces %d go to %d but he can't go next position becacuse it block by allay block %d pieces , %d pieces and %d pieces\n", player->playercolor, piecesNum[0], previousCurrentPiecesPosition, allayPieces[0], allayPieces[1], allayPieces[2]);
                    rollNum = 0;
                    player->pieces[piecesNum[0]].piecesPosition--;
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                }
                if (*picesToHome == 5 && rollNum == 1 && newPositionEnemyPlayerPieces == 0)
                {
                    printf("%c pieces %d capture %c player %d pieces \n", player->playercolor, piecesNum[0], player[enemyPlayer].playercolor, enemyPieces[0]);
                    rollNum = 0;
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                    player->pieces[piecesNum[0]].piecesCaptured=1;
                    piecesCaptured(enemyPlayer, enemyPieces[0], 0, 0, player, borad);
                }
                // mystry case
            }
            // one BLOCK
            if (previousPlayerpieces == 1)
            {

                if (newPositionEnemyPlayerPieces == 2)
                {
                    printf("%c player  BLOCK->(%d & %d) go to %d but he can't go next position becacuse it block by enemy %c player block->(%d pieces and %d pieces and %d pieces)\n", player->playercolor, piecesNum[0], piecesNum[1], previousCurrentPiecesPosition, player[enemyPlayer].playercolor, enemyPieces[0], enemyPieces[1], enemyPieces[2]);
                    rollNum = 0;
                    player->pieces[piecesNum[0]].piecesPosition--;
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                    player->pieces[piecesNum[1]].piecesPosition--;
                    pieces[*playerNum][piecesNum[1]] = player->pieces[piecesNum[1]].piecesPosition;
                }
                if (*picesToHome == 3 && rollNum == 1 && newPositionAllayPlayerPieces == 0)
                {
                    printf("%c player BLOCK->(%d & %d) go to %d make a super block with %d pieces\n", player->playercolor, piecesNum[0], piecesNum[1], newCurrentPiecesPosition, piecesNum[0]);
                    int cureentPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                    int newPiecesDirection = player->pieces[piecesNum[0]].piecesDirection;
                    blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection,0,piecesNum[0], allayPieces);
                    // handle for block for future use
                    player->piecesBlock = 1;
                    player->pieces[piecesNum[0]].piecesBlock = 2;
                    player->pieces[allayPieces[0]].piecesBlock = 2;
                    player->pieces[piecesNum[1]].piecesBlock = 2;
                    // end while loop
                    rollNum = 0;
                    // assing  new position to pieces
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                    pieces[*playerNum][piecesNum[1]] = player->pieces[piecesNum[1]].piecesPosition;
                    pieces[*playerNum][allayPieces[0]] = player->pieces[allayPieces[0]].piecesPosition;
                }
                if(*picesToHome ==3 && rollNum == 1 && newPositionAllayPlayerPieces == 1)
                {
                    printf("%c player BLOCK->(%d & %d)go to %d position but he can't go next position becacuse it block by allay super block->(%d & %d & %d) \n", player->playercolor, piecesNum[0], piecesNum[1], previousCurrentPiecesPosition, allayPieces[0], allayPieces[1], allayPieces[2]);
                    //end while loop
                    rollNum = 0;
                    //go  back to previous position
                    player->pieces[piecesNum[0]].piecesPosition--;
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                    player->pieces[piecesNum[1]].piecesPosition--;
                    pieces[*playerNum][piecesNum[1]] = player->pieces[piecesNum[1]].piecesPosition;
                }
                if (*picesToHome == 6 && rollNum == 1 && newPositionEnemyPlayerPieces == 0)
                {
                    printf("%c player Block->(%d & %d) capture %c player %d pieces \n", player->playercolor,piecesNum[0],piecesNum[1], player[enemyPlayer].playercolor, enemyPieces[0]);
                    //end  while loop
                    rollNum = 0;
                    //store  the position of pieces
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                    pieces[*playerNum][piecesNum[1]] = player->pieces[piecesNum[1]].piecesPosition;
                    //store he capture one pieces
                    player->pieces[piecesNum[0]].piecesCaptured++;
                    player->pieces[piecesNum[1]].piecesCaptured++;
                    //captured pieces go back to base
                    piecesCaptured(enemyPlayer, enemyPieces[0], 0, 0, player, borad);
                }
                if(*picesToHome==6 && rollNum == 1 && newPositionEnemyPlayerPieces == 1)
                {
                    printf("%c player Block->(%d & %d) capture %c player %d pieces and %d pieces \n", player->playercolor,piecesNum[0],piecesNum[1], player[enemyPlayer].playercolor, enemyPieces[0], enemyPieces[1]);
                    rollNum==0;
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                    pieces[*playerNum][piecesNum[1]] = player->pieces[piecesNum[1]].piecesPosition;
                    //store block capture block 
                    player->pieces[piecesNum[0]].piecesCaptured++;
                    player->pieces[piecesNum[1]].piecesCaptured++;
                    //captured  block go back to base
                    piecesCaptured(enemyPlayer, enemyPieces[0], enemyPieces[1], 0, player, borad);
                }
                //mestry cell
            }
            //super block
            if(previousPlayerpieces==2)
            {
                if (newPositionEnemyPlayerPieces == 2 && rollNum!=1)
                {
                    printf("%c player  BLOCK->(%d & %d & %d) go to %d but he can't go next position becacuse it block by enemy %c player block->(%d pieces and %d pieces and %d pieces)\n", player->playercolor, piecesNum[0], piecesNum[1],piecesNum[2], previousCurrentPiecesPosition, player[enemyPlayer].playercolor, enemyPieces[0], enemyPieces[1], enemyPieces[2]);
                    rollNum = 0;
                    player->pieces[piecesNum[0]].piecesPosition--;
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                    player->pieces[piecesNum[1]].piecesPosition--;
                    pieces[*playerNum][piecesNum[1]] = player->pieces[piecesNum[1]].piecesPosition;
                    player->pieces[piecesNum[2]].piecesPosition--;
                    pieces[*playerNum][piecesNum[2]] = player->pieces[piecesNum[2]].piecesPosition;
                }
                if (*picesToHome == 7 && rollNum == 1 && newPositionEnemyPlayerPieces == 0)
                {
                    printf("%c player Block->(%d & %d & %d) capture %c player %d pieces \n", player->playercolor, piecesNum[0], piecesNum[1],piecesNum[2], player[enemyPlayer].playercolor, enemyPieces[0]);
                    // end  while loop
                    rollNum = 0;
                    // store  the position of pieces
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                    pieces[*playerNum][piecesNum[1]] = player->pieces[piecesNum[1]].piecesPosition;
                    pieces[*playerNum][piecesNum[2]] = player->pieces[piecesNum[2]].piecesPosition;
                    // store he capture one pieces
                    player->pieces[piecesNum[0]].piecesCaptured++;
                    player->pieces[piecesNum[1]].piecesCaptured++;
                    player->pieces[piecesNum[2]].piecesCaptured++;
                    // captured pieces go back to base
                    piecesCaptured(enemyPlayer, enemyPieces[0], 0, 0, player, borad);
                }
                if (*picesToHome == 7 && rollNum == 1 && newPositionEnemyPlayerPieces == 1)
                {
                    printf("%c player Block->(%d & %d & %d) capture %c player %d pieces and %d pieces \n", player->playercolor, piecesNum[0], piecesNum[1],piecesNum[2], player[enemyPlayer].playercolor, enemyPieces[0], enemyPieces[1]);
                    rollNum == 0;
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                    pieces[*playerNum][piecesNum[1]] = player->pieces[piecesNum[1]].piecesPosition;
                    pieces[*playerNum][piecesNum[2]] = player->pieces[piecesNum[2]].piecesPosition;

                    // store block capture block
                    player->pieces[piecesNum[0]].piecesCaptured++;
                    player->pieces[piecesNum[1]].piecesCaptured++;
                    player->pieces[piecesNum[2]].piecesCaptured++;
                    // captured  block go back to base
                    piecesCaptured(enemyPlayer, enemyPieces[0], enemyPieces[1], 0, player, borad);
                }
                if (*picesToHome == 7 && rollNum == 1 && newPositionEnemyPlayerPieces == 2)
                {
                    printf("%c player Block->(%d & %d & %d) capture %c player %d pieces and %d pieces and %d pieces \n", player->playercolor, piecesNum[0], piecesNum[1], piecesNum[2], player[enemyPlayer].playercolor, enemyPieces[0], enemyPieces[1], enemyPieces[2]);
                    rollNum = 0;
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                    pieces[*playerNum][piecesNum[1]] = player->pieces[piecesNum[1]].piecesPosition;
                    pieces[*playerNum][piecesNum[2]] = player->pieces[piecesNum[2]].piecesPosition;
                    // store block capture block
                    player->pieces[piecesNum[0]].piecesCaptured++;
                    player->pieces[piecesNum[1]].piecesCaptured++;
                    player->pieces[piecesNum[2]].piecesCaptured++;
                    // captured  block go back to base
                    piecesCaptured(enemyPlayer, enemyPieces[0], enemyPieces[1], enemyPieces[2], player, borad);
                }
                //mystry cell
            }
            // 0ne pieces
            if (previousPlayerpieces == 0 && sixTimesBlock == 1)
            {
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

                if ( rollNum == 1 && newPositionAllayPlayerPieces == 0)
                {
                    int cureentPiecesDirection = player->pieces[*piecesNum].piecesDirection;
                    int newPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                    // block direction checker
                    blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection, 0, *piecesNum, allayPieces);
                    // print what happend
                    printf("%c pieces %d go to %d make a block with %d pieces\n", player->playercolor, *piecesNum, newCurrentPiecesPosition, allayPieces[0]);
                    // handle for block for future use
                    player->piecesBlock++;
                    player->pieces[*piecesNum].piecesBlock = 1;
                    player->pieces[allayPieces[0]].piecesBlock = 1;
                    // end while loop
                    rollNum = 0;
                    // assing  new position to pieces
                    pieces[*playerNum][*piecesNum] = player->pieces[*piecesNum].piecesPosition;
                    pieces[*playerNum][allayPieces[0]] = player->pieces[*piecesNum].piecesPosition;
                }
                if (rollNum == 1 && newPositionAllayPlayerPieces == 1)
                {
                    int cureentPiecesDirection = player->pieces[*piecesNum].piecesDirection;
                    int newPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                    int newSecondDirection = player->pieces[allayPieces[1]].piecesDirection;
                    blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection, newSecondDirection, *piecesNum, allayPieces);
                    // handle for block for future use
                    player->piecesBlock++;
                    player->pieces[*piecesNum].piecesBlock = 2;
                    player->pieces[allayPieces[0]].piecesBlock = 2;
                    player->pieces[allayPieces[1]].piecesBlock = 2;
                    // print what happend
                    printf("%c pieces %d go to %d make a super bolck with %d pieces and %d pieces\n", player->playercolor, *piecesNum, newCurrentPiecesPosition, allayPieces[0], allayPieces[1]);
                    // end while loop
                    rollNum = 0;
                    // assing  new position to pieces
                    pieces[*playerNum][allayPieces[0]] = player->pieces[allayPieces[0]].piecesPosition;
                    pieces[*playerNum][allayPieces[1]] = player->pieces[allayPieces[1]].piecesPosition;
                    pieces[*playerNum][*piecesNum] = player->pieces[*piecesNum].piecesPosition;
                }
                if ( rollNum == 1 && newPositionAllayPlayerPieces == 2)
                {
                    printf("%c pieces %d go to %d but he can't go next position becacuse it block by allay block %d pieces , %d pieces and %d pieces\n", player->playercolor, *piecesNum, previousCurrentPiecesPosition, allayPieces[0], allayPieces[1], allayPieces[2]);
                    rollNum = 0;
                    player->pieces[*piecesNum].piecesPosition--;
                    pieces[*playerNum][*piecesNum] = player->pieces[*piecesNum].piecesPosition;
                }
                if (rollNum == 1 && newPositionEnemyPlayerPieces == 0)
                {
                    printf("%c pieces %d capture %c player %d pieces \n", player->playercolor, *piecesNum, player[enemyPlayer].playercolor, enemyPieces[0]);
                    rollNum = 0;
                    pieces[*playerNum][*piecesNum] = player->pieces[*piecesNum].piecesPosition;
                    player->pieces[*piecesNum].piecesCaptured = 1;
                    piecesCaptured(enemyPlayer, enemyPieces[0], 0, 0, player, borad);
                }
                // mystry case
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
            if (pieces[i][j] == position && currentPlayer != i)
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

    // Return the count (which will be 1, 2, or 3)
    if (count == 3 && position == base)
    {
        return 0; // Return 0 if four pieces are in the same position, or the position is -1
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
                if (allayPieces[0] == 0 && j != *piecesNum)
                {
                    allayPieces[0] = j;
                    count++;
                }
                else if (allayPieces[0] > 0 && allayPieces[1] == 0 && j != *piecesNum)
                {
                    allayPieces[1] = j;
                    count++;
                }
                else if (allayPieces[1] > 0 && allayPieces[2] == 0 && allayPieces[0] > 0 && j != *piecesNum)

                {
                    allayPieces[2] = j;
                    count++;
                }
            }
        }
    }
    if (count == 3 && position == base)
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

void piecesCaptured(int enemyPlayer, int firstpieces, int secondpieces, int thirdpieces, Player *player, Borad *borad)
{
    player = &player[enemyPlayer];
    if (firstpieces > 0 && secondpieces == 0 && thirdpieces == 0)
    {
        player->pieces[firstpieces].pastHomeHowTimes = 0;
        player->pieces[firstpieces].pastpiecesDirection = 0;
        player->pieces[firstpieces].piecesCaptured = 0;
        player->pieces[firstpieces].piecesDirection = 0;
        player->pieces[firstpieces].piecesPosition = base;
        player->pieces[firstpieces].startgame = -1;
    }
    if (firstpieces > 0 && secondpieces > 0 && thirdpieces == 0)
    { // first player go to base
        player->pieces[firstpieces].pastHomeHowTimes = 0;
        player->pieces[firstpieces].pastpiecesDirection = 0;
        player->pieces[firstpieces].piecesCaptured = 0;
        player->pieces[firstpieces].piecesDirection = 0;
        player->pieces[firstpieces].piecesPosition = base;
        player->pieces[firstpieces].startgame = -1;

        // second player go to base
        player->pieces[secondpieces].pastHomeHowTimes = 0;
        player->pieces[secondpieces].pastpiecesDirection = 0;
        player->pieces[secondpieces].piecesCaptured = 0;
        player->pieces[secondpieces].piecesDirection = 0;
        player->pieces[secondpieces].piecesPosition = base;
        player->pieces[secondpieces].startgame = -1;

        // remove block from player
        player->piecesBlock--;
        borad->piecesBlock = 0;
    }
    if (firstpieces > 0 && secondpieces > 0 && thirdpieces > 0)
    { // first pieces go to base
        player->pieces[firstpieces].pastHomeHowTimes = 0;
        player->pieces[firstpieces].pastpiecesDirection = 0;
        player->pieces[firstpieces].piecesCaptured = 0;
        player->pieces[firstpieces].piecesDirection = 0;
        player->pieces[firstpieces].piecesPosition = base;
        player->pieces[firstpieces].startgame = -1;

        // second pieces go to base
        player->pieces[secondpieces].pastHomeHowTimes = 0;
        player->pieces[secondpieces].pastpiecesDirection = 0;
        player->pieces[secondpieces].piecesCaptured = 0;
        player->pieces[secondpieces].piecesDirection = 0;
        player->pieces[secondpieces].piecesPosition = base;
        player->pieces[secondpieces].startgame = -1;

        // thirdpieces go to  base
        player->pieces[thirdpieces].pastHomeHowTimes = 0;
        player->pieces[thirdpieces].pastpiecesDirection = 0;
        player->pieces[thirdpieces].piecesCaptured = 0;
        player->pieces[thirdpieces].piecesDirection = 0;
        player->pieces[thirdpieces].piecesPosition = base;
        player->pieces[thirdpieces].startgame = -1;

        // remove block from player
        player->piecesBlock--;
        borad->piecesBlock = 0;
    }
}
void blockBreaker(Player *player,Borad *borad,int allayplayer,int pieces1,int pieces2,int pieces3)
{
    player=&player[allayplayer];
    if(pieces1>0&&pieces2==0&&pieces3==0)
    {
        player->pieces[pieces1].piecesDirection=player->pieces[pieces1].pastpiecesDirection;
        player->pieces[pieces1].pastpiecesDirection=0;
        player->pieces[pieces1].piecesBlock=0;
    }
    if (pieces1>0 &&pieces2>0&&pieces3==0)
    {   //reset block to two pieces
        //first pieces
        player->pieces[pieces1].piecesDirection=player->pieces[pieces1].pastpiecesDirection;
        player->pieces[pieces1].pastpiecesDirection=0;
        player->pieces[pieces1].piecesBlock=0;
        //second pieces
        player->pieces[pieces2].piecesDirection=player->pieces[pieces2].pastpiecesDirection;
        player->pieces[pieces2].pastpiecesDirection=0;
        player->pieces[pieces2].piecesBlock=0;        
    }
    if (pieces1>0 && pieces2>0 &&pieces3>0)
    {
        //reset block to three pieces
        //first pieces
        player->pieces[pieces1].piecesDirection=player->pieces[pieces1].pastpiecesDirection;
        player->pieces[pieces1].pastpiecesDirection=0;
        player->pieces[pieces1].piecesBlock=0;
        //second pieces
        player->pieces[pieces2].piecesDirection=player->pieces[pieces2].pastpiecesDirection;
        player->pieces[pieces2].pastpiecesDirection=0;
        player->pieces[pieces2].piecesBlock=0;
        //third pieces
        player->pieces[pieces3].piecesDirection=player->pieces[pieces3].pastpiecesDirection;
        player->pieces[pieces3].pastpiecesDirection=0;
        player->pieces[pieces3].piecesBlock=0;                 
    }
}
//call player depend on player number
void playerCall(Player *player,Borad *borad,int playerNum,int*piecesToHome,int rollNum,int (*piecesNum[2]),int pieces[4][4])
{
    if (player[playerNum].playercolor=='G')
    {
        greenplayer(&player[playerNum],&borad,rollNum,&(*piecesToHome),&(*piecesNum[2]));
    }
    if (player[playerNum].playercolor=='R')
    {
        redplayer(&player[playerNum],&borad,rollNum,&(*piecesToHome),&(*piecesNum[2]));
    }
    if (player[playerNum].playercolor=='B')
    {
        blueplayer(&player[playerNum],&borad,rollNum,&(*piecesToHome),&(*piecesNum[2]));
    }
    if (player[playerNum].playercolor=='Y')
    {
        yellowplayer(&player[playerNum],&borad,rollNum,&(*piecesToHome),&(*piecesNum[2]));
    }   
}
void mystryCell(Player *player, Borad *borad,int firstPiece,int secondPiece,int thirdPiece,int *movementModifier,int *trunSkipper,int pieces[numPlayers][4])
{
    int mystryCellBeheviros=(rand()%6)+1;
    int allayPieces[3]={0,0,0};
    if (firstPiece>0 && secondPiece==0 && thirdPiece==0)
    {
        if (mystryCellBeheviros==1)
        {
            int bawanaBeheviours=(rand()%2)+1;
            if (bawanaBeheviours==1)
            {
                *movementModifier = 2;     
            }else
            {
                *movementModifier =0.5;
            }
            
        }if (mystryCellBeheviros==2)
        {
            *trunSkipper=4;
            player->pieces[firstPiece].piecesPosition=KotuwaCell;
            pritnf("Next four turn will be skipped for player %c pieces %d\n",player->playercolor,firstPiece);
        }
        if (mystryCellBeheviros==3)
        {
            
        }
        
        
    }
    

}

void handleMysteryCell(int *position, int *direction, int *turnsSkipped, int *movementModifier) 
{
    // Randomly select one of the six options
    srand(time(0));
    int randomChoice = rand() % 6;

    switch(randomChoice) {
        case 0: // Bhawana
            *position = bawanaCell;
            // Randomly determine if the piece is energized or sick
            if (rand() % 2 == 0) {
                *movementModifier = 2; // Energized, movement doubled
            } else {
                *movementModifier = 0.5; // Sick, movement halved
            }
            break;
        case 1: // Kotuwa
            *position = KotuwaCell;
            *turnsSkipped = 4; // Skip 4 turns
            break;
        case 2: // Pita-Kotuwa
            *position =PitaKotuwaCell;
            if (*direction == 1) {
                *direction = -1; // Change direction to counterclockwise
            } else {
                *position = KotuwaCell; // Teleport to Kotuwa
                *turnsSkipped = 4;
            }
            break;
        case 3: // Base
            *position = 0; // Assuming 0 is the base position
            break;
        case 4: // X of the piece color
            // You need to define X based on the piece color
            // This is just a placeholder
            *position = 15; // Example position for X
            break;
        case 5: // Approach of the piece color
            // You need to define the approach cell based on the piece color
            // This is just a placeholder
            *position = 5; // Example position for Approach
            break;
    }
}

void greenplayer(Player *player, Borad *borad, int rollNum, int *piecesToHome, int *piecesNum)

{

    if (rollNum == 6)
    {
        for (int i = 0; i < numPlayers; i++)
        {
            if (player->pieces[i].piecesPosition == base) // not home in base

            {
                piecesNum = i;
                *piecesToHome = 1;
            }
        }
    }
}