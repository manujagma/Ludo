#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define base -1
#define startPoint 0
#define numPlayers 4
#define Borad_size 51  // player pieces
#define greenHome 0000 // please assign value
#define bawanaCell 9
#define KotuwaCell 27
#define PitaKotuwaCell 46
#define redHome 00
#define blueHome 91
#define yellowHome 18


int HomeLabels[5] = {1,2,3,4,5};

typedef struct
{
    int piecesCaptured;
    int piecesPosition;
    int startgame;
    int piecesDirection;
    short pastHomeHowTimes;
    short pastpiecesDirection;
    int piecesBlock;
    int pieceInHomeCell;
    int mystryCellTurns;
    int movementModifier;
    int turnSkkiped;
    int mysteryCell;

} Pieces;
// player area
typedef struct Player
{
    Pieces pieces[4]; // make 4 for pieces for one player
    char playercolor;
    int startGamePieces;
    short piecesBlock;
    int finishPieces;
    

} Player;
typedef struct Borad
{

    short piecesName;
    short piecesBlock;
    short mysteryCell;

} Borad;
    int pieces[4][4] = {{base, base, base, base},{base, base, base, base}, {base, base, base, base},{base, base, base, base}};

    /*
    player1    pieces[0][0] = 0  pieces[0][1] = 0  pieces[0][2] = 0  pieces[0][3] = 0
    player2    pieces[1][0] = 0  pieces[1][1] = 0  pieces[1][2] = 0  pieces[1][3] = 0
    player3    pieces[2][0] = 0  pieces[2][1] = 0  pieces[2][2] = 0  pieces[2][3] = 0
    player4    pieces[3][0] = 0  pieces[3][1] = 0  pieces[3][2] = 0  pieces[3][3] = 0
    */

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
void playermove(int *playerNum, int piecesNum[3], int rollNum, int *picesToHome,int sixTimesBlock,int howManyPiecesStart );
int playerstart(int *startPlayer);
void playerInstall(Player *player);
void boradconst(Player *player, Borad *borad);
int countEnemyPiecesAtPosition(int position, int currentPlayer, int *enemyIndex, int (*enemyPieces)[3]);
int countAllyPiecesAtPosition(int position, int currentPlayer, int (*allayPieces)[3], int *piecesNum);
void blockDirectionChecker(Player *player, Borad *borad, int cureentPiecesDirection, int newPiecesDirection, int newSecondPiecesDirection, int piecesNum, int *allayPieces);
void piecesCaptured(int enemyPlayer, int firstpieces, int secondpieces, int thirdpieces, Player *player, Borad *borad);
void blockBreaker(Player *player,Borad *borad,int allayplayer,int pieces1,int pieces2,int pieces3);
void playerCall(Player *player,Borad *borad,int playerNum,int*piecesToHome,int rollNum,int (*piecesNum[3]));
void mystryCell(Player *player, Borad *borad,int firstPiece,int secondPiece,int thirdPiece,int cureentplayer);
void greenplayer(Player *player,Borad *borad,int playerNum,int rollNum,int *piecesToHome,int (*piecesNum[3]));
void yellowplayer(Player *player,Borad *borad,int playerNum,int rollNum,int *piecesToHome,int (*piecesNum[3]));
void redplayer(Player *player,Borad *borad,int playerNum,int rollNum,int *piecesToHome,int (*piecesNum[3]));
void blueplayer(Player *player,Borad *borad,int playerNum,int rollNum,int *piecesToHome,int (*piecesNum[3]));



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
    boradconst(player, borad);
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
    int *piecesNum[3] = {0, 0, 0};
    int howManyPiecesStart = 0;
    int picesToHome = 0;
    int howManyTimesPlay[numPlayers] = {0, 0, 0, 0};
    int checkSixTimes = 0;
    int countRound = 0;
    while (1)
    {

        // role dice
        rollNum = roll();
        if (rollNum == 6)
        {

            checkSixTimes++;
            if (checkSixTimes == 3)
            {
                for (int i = 0; i < 4; i++)
                {
                    if (player[playerNum].pieces[i].mysteryCell == 1 && player[playerNum].pieces[i].turnSkkiped > 0 && player[playerNum].pieces[i].piecesPosition == KotuwaCell)
                    {
                        player[playerNum].pieces[i].pastHomeHowTimes = 0;
                        player[playerNum].pieces[i].pastpiecesDirection = 0;
                        player[playerNum].pieces[i].piecesCaptured = 0;
                        player[playerNum].pieces[i].piecesDirection = 0;
                        player[playerNum].pieces[i].piecesPosition = base;
                        player[playerNum].pieces[i].startgame = -1;
                        pieces[playerNum][i] = base;
                        printf("%c player %d pieces go to base because he trapped in Kotuwa cell\n", player[playerNum].playercolor, i);
                    }
                }

                if (player[playerNum].piecesBlock == 1)
                {
                    int array[2] = {0, 0};
                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {

                            if (i != j && player[playerNum].pieces[i].piecesBlock == 1 && player[playerNum].pieces[j].piecesBlock == 1)
                            {
                                if (player[playerNum].pieces[i].piecesPosition == player[playerNum].pieces[j].piecesPosition)
                                {
                                    if (array[0] == 0)
                                    {
                                        array[0] = i;
                                    }
                                    else if (array[1] == 0)
                                    {
                                        array[1] = i;
                                    }
                                }
                            }
                        }
                    }
                    int arry1[3] = { array[0],-1,-1};
                    playermove(&playerNum, arry1, 6, 0, 1, howManyPiecesStart);
                    int arry2[3] = {array[2], -1, -1};
                    playermove(&playerNum, arry2, 6, 0, 1, howManyPiecesStart);
                    // break down block and move them six times
                    blockBreaker(player, borad, playerNum, array[0], array[1], -1);
                }
            }
        }
        howManyTimesPlay[playerNum]++;
        playerCall(player, borad, playerNum, &picesToHome, rollNum, piecesNum);
        playermove(&playerNum, piecesNum[3], rollNum, &picesToHome, 0, howManyPiecesStart);
        playerNum++;
        if (howManyTimesPlay[0] != 0 && howManyTimesPlay[0] == howManyTimesPlay[1] && howManyTimesPlay[1] == howManyTimesPlay[2] && howManyTimesPlay[2] == howManyTimesPlay[3])
        {
            countRound++;
            if (howManyPiecesStart > 2 && (howManyTimesPlay[0] % 4) == 1)
            {
                int stop = 1;
                while (stop)
                {
                    int mystryNum = roll() % 52;
                    if (borad[mystryNum].mysteryCell != 1)
                    {
                        borad[mystryNum].mysteryCell = 1;
                        stop = 0;
                    }
                }
            }

            //print what is status of all players position 
            printPlayers(player);
            printf("this is %d round\n",countRound);
        }

        playerNum%=4;
        // stay behind of players and borad (go around like circule)
    }
}
void playermove(int *playerNum, int piecesNum[3], int rollNum, int *picesToHome,int sixTimesBlock,int howManyPiecesStart )
{
    // in this function only do move pieces and cut enmy pieces and go to mystrey cell
    Borad *borad;
    Player *player = &player[*playerNum];
    

    int enemyPlayer = 0;

    while (rollNum==0)
    {
        int enemyPieces[3] = {-1, -1, -1};
        int allayPieces[3] = {-1, -1, -1};
        int piecesNum[3] = {-1, -1,-1};

        // give picecs to X location from base

        if (*picesToHome == 1)
        {
            player->pieces[piecesNum[0]].piecesPosition = base;
            player->pieces[piecesNum[0]].startgame = 1;
            player->pieces[piecesNum[0]].piecesCaptured = 0;
            player->pieces[piecesNum[0]].pastHomeHowTimes = 0;
            player->pieces[piecesNum[0]].pastpiecesDirection = 0;
            player->pieces[piecesNum[0]].pieceInHomeCell=0;
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
            int assignedCount = 0;

            for (int i = 0; i < 3; i++)
            {
                if (piecesNum[i] != -1)
                {
                    assignedCount++;
                }
            }
            int newPositionEnemyPlayerPieces = countEnemyPiecesAtPosition(newCurrentPiecesPosition, *playerNum, &enemyPlayer, &enemyPieces);
            int newPositionAllayPlayerPieces = countAllyPiecesAtPosition(newCurrentPiecesPosition, *playerNum, &allayPieces, &piecesNum[0]);
            if (piecesNum[1] > 0)
            {
                player->pieces[piecesNum[1]].piecesPosition++;
            }
            if (piecesNum[2]>0)
            {
                player->pieces[piecesNum[2]].piecesPosition++;
            }

            // 0ne pieces
            if (assignedCount == 1 &&(sixTimesBlock==0 || sixTimesBlock==1))
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

                if ((*picesToHome==10 || *picesToHome == 2) && rollNum == 1 && newPositionAllayPlayerPieces == 1)
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
                if ((*picesToHome==10 || *picesToHome == 2) && rollNum == 1 && newPositionAllayPlayerPieces == 2)
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
                if ((*picesToHome==10 || *picesToHome == 2) && rollNum == 1 && newPositionAllayPlayerPieces == 3)
                {
                    printf("%c pieces %d go to %d but he can't go next position becacuse it block by allay block %d pieces , %d pieces and %d pieces\n", player->playercolor, piecesNum[0], previousCurrentPiecesPosition, allayPieces[0], allayPieces[1], allayPieces[2]);
                    rollNum = 0;
                    player->pieces[piecesNum[0]].piecesPosition--;
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                }
                if ((*picesToHome==10 || *picesToHome == 5) && rollNum == 1 && newPositionEnemyPlayerPieces == 0)
                {
                    printf("%c pieces %d capture %c player %d pieces \n", player->playercolor, piecesNum[0], player[enemyPlayer].playercolor, enemyPieces[0]);
                    rollNum = 0;
                    pieces[*playerNum][piecesNum[0]] = player->pieces[piecesNum[0]].piecesPosition;
                    player->pieces[piecesNum[0]].piecesCaptured=1;
                    piecesCaptured(enemyPlayer, enemyPieces[0], 0, 0, player, borad);
                }
                if ((*picesToHome==10 || *picesToHome == 8) && rollNum==1 && borad[newCurrentPiecesPosition].mysteryCell==1)
                {
                    if (newPositionAllayPlayerPieces==0)
                    {
                        mystryCell(&player[*playerNum],borad,piecesNum[0],-1,-1,*playerNum);
                        rollNum=0;
                    }
                    else if (newPositionEnemyPlayerPieces==1)
                    {
                        mystryCell(&player[*playerNum],borad,piecesNum[0],-1,-1,*playerNum);
                        rollNum=0;
                    }
                    else
                    {
                    if (newPositionAllayPlayerPieces==1)
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
                    if (newPositionAllayPlayerPieces==2)
                    {
                        int cureentPiecesDirection = player->pieces[*piecesNum].piecesDirection;
                    int newPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                    int newSecondDirection = player->pieces[allayPieces[1]].piecesDirection;
                    blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection, newSecondDirection, piecesNum[0], allayPieces);
                    // handle for block for future use
                    player->piecesBlock++;
                    player->pieces[piecesNum[0]].piecesBlock = 2;
                    }
                    }
                }

                if (player->pieces[piecesNum[0]].piecesCaptured >= 1)
                {
                    if (player->playercolor == 'G' && player->pieces[piecesNum[0]].piecesPosition == greenHome)
                    {
                        player->pieces[piecesNum[0]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[0]].pieceInHomeCell = 1;
                        rollNum--;
                        printf("%c player pieces %d go to H%d\n", player->playercolor, piecesNum, player->pieces[piecesNum[0]].piecesPosition);
                    }
                    if (player->playercolor == 'R' && player->pieces[piecesNum[0]].piecesPosition == redHome)
                    {
                        player->pieces[piecesNum[0]].piecesPosition = HomeLabels[1];
                        player->pieces[piecesNum[0]].pieceInHomeCell = 1;
                        rollNum--;
                        printf("%c player pieces %d go to H%d\n", player->playercolor, piecesNum, player->pieces[piecesNum[0]].piecesPosition);
                    }
                    if (player->playercolor == 'G' && player->pieces[piecesNum[0]].piecesPosition == yellowHome)
                    {
                        player->pieces[piecesNum[0]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[0]].pieceInHomeCell = 1;
                        rollNum--;
                        printf("%c player pieces %d go to H%d\n", player->playercolor, piecesNum, player->pieces[piecesNum[0]].piecesPosition);
                    }
                    if (player->playercolor == 'R' && player->pieces[piecesNum[0]].piecesPosition == blueHome)
                    {
                        player->pieces[piecesNum[0]].piecesPosition = HomeLabels[1];
                        player->pieces[piecesNum[0]].pieceInHomeCell = 1;
                        rollNum--;
                        printf("%c player pieces %d go to H%d\n", player->playercolor, piecesNum, player->pieces[piecesNum[0]].piecesPosition);
                    }
                }
                if (player->pieces[piecesNum[0]].pieceInHomeCell==1)
                {
                    int couter=0;
                    for (int  i = 0; i <=5; i++)
                    {

                       if(player->pieces[piecesNum[0]].piecesPosition==HomeLabels[i])
                       {
                            couter=i+1;
                            if ((couter+rollNum)==5)
                            {
                                player->pieces[piecesNum[0]].startgame=0;
                                player[*playerNum].finishPieces=player[*playerNum].finishPieces+1;
                                printf("%c player pieces %d go to home\n",player->playercolor,piecesNum[0]);
                                rollNum=0;
                            }
                            if ((couter+rollNum)<5)
                            {
                                player->pieces[piecesNum[0]].piecesPosition=HomeLabels[i+rollNum];
                                printf("%c player pieces %d go to H%d\n",player->playercolor,piecesNum[0],player->pieces[piecesNum[0]].piecesPosition);
                                rollNum=0;

                            }
                            if ((couter+rollNum)>5)
                            {
                                printf("%c player pieces %d can't move in home cells\n",player->playercolor,piecesNum[0]);
                                rollNum=0;
                            }  
                       }
                    }
                    
                }
                
                
                // mystry case
            }
            // one BLOCK
            if (assignedCount == 2)
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
                    blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection,allayPieces[0],piecesNum[0], allayPieces);
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
                               if (player->pieces[piecesNum[0]].piecesCaptured >= 1 || player->pieces[piecesNum[1]].piecesCaptured >= 1)

                {
                    if (player->playercolor == 'G' && player->pieces[piecesNum[0]].piecesPosition == greenHome)
                    {
                        player->pieces[piecesNum[0]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].pieceInHomeCell = 1;
                        player->pieces[piecesNum[0]].pieceInHomeCell = 1;
                        rollNum--;
                        printf("%c player block-> (%d&%d) go to H%d\n", player->playercolor, piecesNum[0],pieces[1], player->pieces[piecesNum[0]].piecesPosition);
                    }
                    if (player->playercolor == 'R' && player->pieces[piecesNum[0]].piecesPosition == redHome)
                    {
                        player->pieces[piecesNum[0]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].pieceInHomeCell = 1;
                        player->pieces[piecesNum[0]].pieceInHomeCell = 1;
                        rollNum--;
                        printf("%c player block-> (%d&%d) go to H%d\n", player->playercolor, piecesNum[0],pieces[1], player->pieces[piecesNum[0]].piecesPosition);
                    }
                    if (player->playercolor == 'G' && player->pieces[piecesNum[0]].piecesPosition == yellowHome)
                    {
                        player->pieces[piecesNum[0]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].pieceInHomeCell = 1;
                        player->pieces[piecesNum[0]].pieceInHomeCell = 1;
                        rollNum--;
                        printf("%c player block-> (%d&%d) go to H%d\n", player->playercolor, piecesNum[0],pieces[1], player->pieces[piecesNum[0]].piecesPosition);
                    }
                    if (player->playercolor == 'R' && player->pieces[piecesNum[0]].piecesPosition == blueHome)
                    {
                        player->pieces[piecesNum[0]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].pieceInHomeCell = 1;
                        player->pieces[piecesNum[0]].pieceInHomeCell = 1;
                        rollNum--;
                        printf("%c player block-> (%d&%d) go to H%d\n", player->playercolor, piecesNum[0],pieces[1], player->pieces[piecesNum[0]].piecesPosition);
                    }
                }
                if (player->pieces[piecesNum[0]].pieceInHomeCell == 1)
                {
                    int couter = 0;
                    for (int i = 0; i <= 5; i++)
                    {

                        if (player->pieces[piecesNum[0]].piecesPosition == HomeLabels[i])
                        {
                            couter = i + 1;
                            if ((couter + rollNum) == 5)
                            {

                                player->pieces[piecesNum[0]].startgame = 0;
                                player->pieces[piecesNum[1]].startgame = 0;
                                player[*playerNum].finishPieces = player[*playerNum].finishPieces + 2;
                                printf("%c player block->(%d&%d) go to home\n", player->playercolor, piecesNum[0], piecesNum[1]);
                                rollNum = 0;
                            }
                            if ((couter + rollNum) < 5)
                            {
                                player->pieces[piecesNum[0]].piecesPosition = HomeLabels[i + rollNum];
                                player->pieces[piecesNum[1]].piecesPosition = HomeLabels[i + rollNum];
                                printf("%c player block->(%d&%d) go to H%d\n", player->playercolor, piecesNum[0], piecesNum[1], player->pieces[piecesNum[0]].piecesPosition);
                                rollNum = 0;
                            }
                            if ((couter + rollNum) > 5)
                            {
                                printf("%c player block->(%d&%d)can't move in home cells\n", player->playercolor, piecesNum[0], piecesNum[1]);
                                rollNum = 0;
                            }
                        }
                    }
                }
                //mestry cell
            }
            //super block
            if(assignedCount==3)
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
                    printf("%c player Block->(%d & %d & %d) capture %c player %d pieces and %d pieces \n", player->playercolor, piecesNum[0], piecesNum[1], piecesNum[2], player[enemyPlayer].playercolor, enemyPieces[0], enemyPieces[1]);
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
                if (player->pieces[piecesNum[0]].piecesCaptured >= 1 || player->pieces[piecesNum[1]].piecesCaptured >= 1 || player->pieces[piecesNum[2]].piecesCaptured >= 1)

                {
                    if (player->playercolor == 'G' && player->pieces[piecesNum[0]].piecesPosition == greenHome)
                    {
                        player->pieces[piecesNum[0]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[2]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].pieceInHomeCell = 1;
                        player->pieces[piecesNum[0]].pieceInHomeCell = 1;
                        player->pieces[piecesNum[2]].pieceInHomeCell = 1;
                        rollNum--;
                        printf("%c player block-> (%d&%d&%d) go to H%d\n", player->playercolor, piecesNum[0], pieces[1], piecesNum[2], player->pieces[piecesNum[0]].piecesPosition);
                    }
                    if (player->playercolor == 'R' && player->pieces[piecesNum[0]].piecesPosition == redHome)
                    {
                        player->pieces[piecesNum[0]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[2]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].pieceInHomeCell = 1;
                        player->pieces[piecesNum[0]].pieceInHomeCell = 1;
                        player->pieces[piecesNum[2]].pieceInHomeCell = 1;
                        rollNum--;
                        printf("%c player block-> (%d&%d&%d) go to H%d\n", player->playercolor, piecesNum[0], pieces[1], piecesNum[2], player->pieces[piecesNum[0]].piecesPosition);
                    }
                    if (player->playercolor == 'G' && player->pieces[piecesNum[0]].piecesPosition == yellowHome)
                    {
                        player->pieces[piecesNum[0]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[2]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].pieceInHomeCell = 1;
                        player->pieces[piecesNum[0]].pieceInHomeCell = 1;
                        player->pieces[piecesNum[2]].pieceInHomeCell = 1;
                        rollNum--;
                        printf("%c player block-> (%d&%d&%d) go to H%d\n", player->playercolor, piecesNum[0], pieces[1], piecesNum[2], player->pieces[piecesNum[0]].piecesPosition);
                    }
                    if (player->playercolor == 'R' && player->pieces[piecesNum[0]].piecesPosition == blueHome)
                    {
                        player->pieces[piecesNum[0]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[2]].piecesPosition = HomeLabels[0];
                        player->pieces[piecesNum[1]].pieceInHomeCell = 1;
                        player->pieces[piecesNum[0]].pieceInHomeCell = 1;
                        player->pieces[piecesNum[2]].pieceInHomeCell = 1;
                        rollNum--;
                        printf("%c player block-> (%d&%d&%d) go to H%d\n", player->playercolor, piecesNum[0], pieces[1], piecesNum[2], player->pieces[piecesNum[0]].piecesPosition);
                    }
                }
                if (player->pieces[piecesNum[0]].pieceInHomeCell == 1)
                {
                    int couter = 0;
                    for (int i = 0; i <= 5; i++)
                    {

                        if (player->pieces[piecesNum[0]].piecesPosition == HomeLabels[i])
                        {
                            couter = i + 1;
                            if ((couter + rollNum) == 5)
                            {

                                player->pieces[piecesNum[0]].startgame = 0;
                                player->pieces[piecesNum[1]].startgame = 0;
                                player->pieces[piecesNum[2]].startgame = 0;

                                player[*playerNum].finishPieces = player[*playerNum].finishPieces + 3;
                                printf("%c player block->(%d&%d&%d) go to home\n", player->playercolor, piecesNum[0], piecesNum[1], piecesNum[2]);
                                rollNum = 0;
                            }
                            if ((couter + rollNum) < 5)
                            {
                                player->pieces[piecesNum[0]].piecesPosition = HomeLabels[i + rollNum];
                                player->pieces[piecesNum[1]].piecesPosition = HomeLabels[i + rollNum];
                                player->pieces[piecesNum[2]].piecesPosition = HomeLabels[i + rollNum];
                                printf("%c player block->(%d&%d&%d) go to H%d\n", player->playercolor, piecesNum[0], piecesNum[1], piecesNum[2], player->pieces[piecesNum[0]].piecesPosition);
                                rollNum = 0;
                            }
                            if ((couter + rollNum) > 5)
                            {
                                printf("%c player block->(%d&%d&%d)can't move in home cells\n", player->playercolor, piecesNum[0], piecesNum[1], piecesNum[2]);
                                rollNum = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}
int countEnemyPiecesAtPosition(int position, int currentPlayer, int *enemyIndex, int (*enemyPieces)[3])
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
                if (*enemyPieces[0] == -1)
                {
                    *enemyPieces[0] = j;
                    count++;
                }
                else if (*enemyPieces[1] == -1 && *enemyPieces[0] > -1)
                {
                    *enemyPieces[1] = j;
                    count++;
                }
                else if (*enemyPieces[2]==-1 && *enemyPieces[1] > -1 && *enemyPieces[0] > -1)
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

int countAllyPiecesAtPosition(int position, int currentPlayer, int (*allayPieces)[3], int *piecesNum)
{
    int count = 0;
    // Iterate over all players and their pieces
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (pieces[i][j] == position && i == currentPlayer)
            {
                if (*allayPieces[0] == -1 && j != *piecesNum)
                {
                    *allayPieces[0] = j;
                    count++;
                }
                else if (*allayPieces[0] > -1 && *allayPieces[1] == -1 && j != *piecesNum)
                {
                    *allayPieces[1] = j;
                    count++;
                }
                else if (*allayPieces[1] > -1 && *allayPieces[2] == -1 && *allayPieces[0] > 0 && j != *piecesNum)

                {
                    *allayPieces[2] = j;
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
    if (firstpieces > -1 && secondpieces == -1 && thirdpieces == -1)
    {
        player->pieces[firstpieces].pastHomeHowTimes = 0;
        player->pieces[firstpieces].pastpiecesDirection = 0;
        player->pieces[firstpieces].piecesCaptured = 0;
        player->pieces[firstpieces].piecesDirection = 0;
        player->pieces[firstpieces].piecesPosition = base;
        player->pieces[firstpieces].startgame = -1;
        pieces[enemyPlayer][firstpieces]=base;
    }
    if (firstpieces > -1 && secondpieces > -1 && thirdpieces == -1)
    { // first player go to base
        player->pieces[firstpieces].pastHomeHowTimes = 0;
        player->pieces[firstpieces].pastpiecesDirection = 0;
        player->pieces[firstpieces].piecesCaptured = 0;
        player->pieces[firstpieces].piecesDirection = 0;
        player->pieces[firstpieces].piecesPosition = base;
        player->pieces[firstpieces].startgame = -1;
        pieces[enemyPlayer][firstpieces]=base;


        // second player go to base
        player->pieces[secondpieces].pastHomeHowTimes = 0;
        player->pieces[secondpieces].pastpiecesDirection = 0;
        player->pieces[secondpieces].piecesCaptured = 0;
        player->pieces[secondpieces].piecesDirection = 0;
        player->pieces[secondpieces].piecesPosition = base;
        player->pieces[secondpieces].startgame = -1;
        pieces[enemyPlayer][secondpieces]=base;

        // remove block from player
        player->piecesBlock--;
        borad->piecesBlock = 0;
    }
    if (firstpieces > -1 && secondpieces > -1 && thirdpieces > -1)
    { // first pieces go to base
        player->pieces[firstpieces].pastHomeHowTimes = 0;
        player->pieces[firstpieces].pastpiecesDirection = 0;
        player->pieces[firstpieces].piecesCaptured = 0;
        player->pieces[firstpieces].piecesDirection = 0;
        player->pieces[firstpieces].piecesPosition = base;
        player->pieces[firstpieces].startgame = -1;
        pieces[enemyPlayer][firstpieces]=base;


        // second pieces go to base
        player->pieces[secondpieces].pastHomeHowTimes = 0;
        player->pieces[secondpieces].pastpiecesDirection = 0;
        player->pieces[secondpieces].piecesCaptured = 0;
        player->pieces[secondpieces].piecesDirection = 0;
        player->pieces[secondpieces].piecesPosition = base;
        player->pieces[secondpieces].startgame = -1;
        pieces[enemyPlayer][secondpieces]=base;


        // thirdpieces go to  base
        player->pieces[thirdpieces].pastHomeHowTimes = 0;
        player->pieces[thirdpieces].pastpiecesDirection = 0;
        player->pieces[thirdpieces].piecesCaptured = 0;
        player->pieces[thirdpieces].piecesDirection = 0;
        player->pieces[thirdpieces].piecesPosition = base;
        player->pieces[thirdpieces].startgame = -1;
        pieces[enemyPlayer][thirdpieces]=base;


        // remove block from player
        player->piecesBlock--;
        borad->piecesBlock = 0;
    }
}
void blockBreaker(Player *player,Borad *borad,int allayplayer,int pieces1,int pieces2,int pieces3)
{
    player=&player[allayplayer];
    if(pieces1>-1&&pieces2==-1&&pieces3==-1)
    {
        player->pieces[pieces1].piecesDirection=player->pieces[pieces1].pastpiecesDirection;
        player->pieces[pieces1].pastpiecesDirection=0;
        player->pieces[pieces1].piecesBlock=0;
    }
    if (pieces1>-1 &&pieces2>-1&&pieces3==-1)
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
    if (pieces1>-1 && pieces2>-1 &&pieces3>-1)
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
void mystryCell(Player *player, Borad *borad, int firstPiece, int secondPiece, int thirdPiece, int cureentplayer)
{
    int mystryCellBeheviros = (rand() % 6) + 1;
    int allayPieces[3] = {-1, -1, -1};
    int enemyPieces[3] = {-1, -1, -1};
    int enemyPlayer = 0;
    if ((firstPiece>0 &&secondPiece>0 && thirdPiece==0) || (firstPiece>0 && secondPiece>0 && thirdPiece>0) )
    {
      printf("can't teleport any block to mystyer cell\n");
    }
    
    if (firstPiece > 0 && secondPiece == 0 && thirdPiece == 0)
    {

        if (mystryCellBeheviros == 1)
        {
            int newPositionEnemyPlayerPieces = countEnemyPiecesAtPosition(bawanaCell, firstPiece, &enemyPlayer, &enemyPieces);
            int newPositionAllayPlayerPieces = countAllyPiecesAtPosition(bawanaCell, cureentplayer, &allayPieces, &firstPiece);
            if (newPositionAllayPlayerPieces == 1)
            {
                int cureentPiecesDirection = player->pieces[firstPiece].piecesDirection;
                int newPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                // block direction checker
                blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection, 0, firstPiece, allayPieces);
                // print what happend
                printf("%c pieces %d teleport to bawana cell->(%d) make a block with %d pieces and that teleport pieces not efficted anything\n", player->playercolor, firstPiece, bawanaCell, allayPieces[0]);
                // handle for block for future use
                player->piecesBlock++;
                player->pieces[firstPiece].piecesBlock = 1;
                player->pieces[allayPieces[0]].piecesBlock = 1;
                player->pieces[firstPiece].piecesPosition = bawanaCell;
                pieces[cureentplayer][allayPieces[0]] = player->pieces[allayPieces[0]].piecesPosition;
                pieces[cureentplayer][firstPiece] = player->pieces[firstPiece].piecesPosition;
            }
            if (newPositionAllayPlayerPieces == 2)
            {
                int cureentPiecesDirection = player->pieces[firstPiece].piecesDirection;
                int newPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                int newSecondDirection = player->pieces[allayPieces[1]].piecesDirection;
                blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection, newSecondDirection, firstPiece, allayPieces);
                // handle for block for future use
                player->piecesBlock++;
                player->pieces[firstPiece].piecesBlock = 2;
                player->pieces[allayPieces[0]].piecesBlock = 2;
                player->pieces[allayPieces[1]].piecesBlock = 2;
                // print what happend
                printf("%c pieces %d teleport to bawana cell->(%d) make a super bolck with %d pieces and %d pieces and that teleport pieces not efficted anything\n", player->playercolor, firstPiece, bawanaCell, allayPieces[0], allayPieces[1]);
                // assing  new position to pieces
                player->pieces[firstPiece].piecesPosition = bawanaCell;
                pieces[cureentplayer][allayPieces[0]] = player->pieces[allayPieces[0]].piecesPosition;
                pieces[cureentplayer][allayPieces[1]] = player->pieces[allayPieces[1]].piecesPosition;
                pieces[cureentplayer][firstPiece] = player->pieces[firstPiece].piecesPosition;
            }
            if (newPositionAllayPlayerPieces == 3)
            {
                printf("%c pieces can't teleport bawana cell->(%d) allay block %d pieces , %d pieces and %d pieces\n", player->playercolor, firstPiece, bawanaCell, allayPieces[0], allayPieces[1], allayPieces[2]);
            }
            if (newPositionEnemyPlayerPieces == 0)
            {
                printf("%c pieces %d teleport to bawana Cell->(%d) capture %c player %d pieces so that teleport piece not efficted anything\n", player->playercolor, firstPiece, bawanaCell, player[enemyPlayer].playercolor, enemyPieces[0]);
                player->pieces[firstPiece].piecesPosition = bawanaCell;
                pieces[cureentplayer][firstPiece] = player->pieces[firstPiece].piecesPosition;
                player->pieces[firstPiece].piecesCaptured = 1;
                piecesCaptured(enemyPlayer, enemyPieces[0], 0, 0, player, borad);
            }
            if (newPositionEnemyPlayerPieces > 0)
            {
                printf("%c player %d piece can't move to bawana cell->(%d) because it block by enemy block\n", player->playercolor, firstPiece, bawanaCell);
            }
            if (newPositionAllayPlayerPieces == 0)
            {

                player->pieces[firstPiece].mysteryCell = 1;
                int bawanaBeheviours = (rand() % 2) + 1;
                if (bawanaBeheviours == 1)
                {
                    player->pieces[firstPiece].movementModifier = 2;
                    player->pieces[firstPiece].mystryCellTurns = 4;
                    printf("now %c player %d pieces is energized for next four rounds\n", player->playercolor, firstPiece);
                }
                else
                {
                    player->pieces[firstPiece].movementModifier = 0.5;
                    player->pieces[firstPiece].mystryCellTurns = 4;
                    printf("now %c player %d pieces is sick for next four rounds\n", player->playercolor, firstPiece);
                }
            }
        }
                if (mystryCellBeheviros==2)
        {
             int newPositionEnemyPlayerPieces = countEnemyPiecesAtPosition(PitaKotuwaCell, firstPiece, &enemyPlayer, &enemyPieces);
            int newPositionAllayPlayerPieces = countAllyPiecesAtPosition(PitaKotuwaCell, cureentplayer, &allayPieces, &firstPiece);
            if (newPositionAllayPlayerPieces == 1)
            {
                int cureentPiecesDirection = player->pieces[firstPiece].piecesDirection;
                int newPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                // block direction checker
                blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection, 0, firstPiece, allayPieces);
                // print what happend
                printf("%c pieces %d teleport to pita Kotuwa cell->(%d) make a block with %d pieces and that teleport pieces not efficted anything\n", player->playercolor, firstPiece, PitaKotuwaCell, allayPieces[0]);
                // handle for block for future use
                player->piecesBlock++;
                player->pieces[firstPiece].piecesBlock = 1;
                player->pieces[allayPieces[0]].piecesBlock = 1;
                player->pieces[firstPiece].piecesPosition =PitaKotuwaCell;
                pieces[cureentplayer][allayPieces[0]] = player->pieces[allayPieces[0]].piecesPosition;
                pieces[cureentplayer][firstPiece] = player->pieces[firstPiece].piecesPosition;
            }
            if (newPositionAllayPlayerPieces == 2)
            {
                int cureentPiecesDirection = player->pieces[firstPiece].piecesDirection;
                int newPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                int newSecondDirection = player->pieces[allayPieces[1]].piecesDirection;
                blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection, newSecondDirection, firstPiece, allayPieces);
                // handle for block for future use
                player->piecesBlock++;
                player->pieces[firstPiece].piecesBlock = 2;
                player->pieces[allayPieces[0]].piecesBlock = 2;
                player->pieces[allayPieces[1]].piecesBlock = 2;
                // print what happend
                printf("%c pieces %d teleport to PitaKotuwa cell->(%d) make a super bolck with %d pieces and %d pieces and that teleport pieces not efficted anything\n", player->playercolor, firstPiece, PitaKotuwaCell, allayPieces[0], allayPieces[1]);
                // assing  new position to pieces
                player->pieces[firstPiece].piecesPosition = KotuwaCell;
                pieces[cureentplayer][allayPieces[0]] = player->pieces[allayPieces[0]].piecesPosition;
                pieces[cureentplayer][allayPieces[1]] = player->pieces[allayPieces[1]].piecesPosition;
                pieces[cureentplayer][firstPiece] = player->pieces[firstPiece].piecesPosition;
            }
            if (newPositionAllayPlayerPieces == 3)
            {
                printf("%c pieces can't teleport PitaKotuwa cell->(%d) allay block %d pieces , %d pieces and %d pieces\n", player->playercolor, firstPiece, PitaKotuwaCell, allayPieces[0], allayPieces[1], allayPieces[2]);
            }
            if (newPositionEnemyPlayerPieces == 0)
            {
                printf("%c pieces %d teleport to PitaKotuwa Cell->(%d) capture %c player %d pieces so that teleport piece not efficted anything\n", player->playercolor, firstPiece, PitaKotuwaCell, player[enemyPlayer].playercolor, enemyPieces[0]);
                player->pieces[firstPiece].piecesPosition = KotuwaCell;
                pieces[cureentplayer][firstPiece] = player->pieces[firstPiece].piecesPosition;
                player->pieces[firstPiece].piecesCaptured = 1;
                piecesCaptured(enemyPlayer, enemyPieces[0], 0, 0, player, borad);
            }
            if (newPositionEnemyPlayerPieces > 0)
            {
                printf("%c player %d piece can't move to PitaKotuwa cell->(%d) because it block by enemy block\n", player->playercolor, firstPiece,PitaKotuwaCell);
            }
            if (newPositionAllayPlayerPieces==0)
            {
                if(player->pieces[firstPiece].piecesDirection==1)
                {
                    player->pieces[firstPiece].piecesDirection==2;
                    printf("%c player %d pieces teleport to pitakottuwa cell->(%d) and that teleport pieces change direction to clockwise to anticlockwise\n",player->playercolor,firstPiece,PitaKotuwaCell);
                
                }else
                {
                    mystryCellBeheviros=3;
                    printf("%c player %d pieces teleport to pitakottuwa cell->(%d) and that teleport cell teleport to kottuwa cell->(%d)",player->playercolor,firstPiece,PitaKotuwaCell,KotuwaCell);
                }
            }
            
            
        }
        if (mystryCellBeheviros == 3)
        {
            int newPositionEnemyPlayerPieces = countEnemyPiecesAtPosition(KotuwaCell, firstPiece, &enemyPlayer, &enemyPieces);
            int newPositionAllayPlayerPieces = countAllyPiecesAtPosition(KotuwaCell, cureentplayer,&allayPieces, &firstPiece);
            if (newPositionAllayPlayerPieces == 1)
            {
                int cureentPiecesDirection = player->pieces[firstPiece].piecesDirection;
                int newPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                // block direction checker
                blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection, 0, firstPiece, allayPieces);
                // print what happend
                printf("%c pieces %d teleport to Kotuwa cell->(%d) make a block with %d pieces and that teleport pieces not efficted anything\n", player->playercolor, firstPiece, KotuwaCell, allayPieces[0]);
                // handle for block for future use
                player->piecesBlock++;
                player->pieces[firstPiece].piecesBlock = 1;
                player->pieces[allayPieces[0]].piecesBlock = 1;
                player->pieces[firstPiece].piecesPosition = KotuwaCell;
                pieces[cureentplayer][allayPieces[0]] = player->pieces[allayPieces[0]].piecesPosition;
                pieces[cureentplayer][firstPiece] = player->pieces[firstPiece].piecesPosition;
            }
            if (newPositionAllayPlayerPieces == 2)
            {
                int cureentPiecesDirection = player->pieces[firstPiece].piecesDirection;
                int newPiecesDirection = player->pieces[allayPieces[0]].piecesDirection;
                int newSecondDirection = player->pieces[allayPieces[1]].piecesDirection;
                blockDirectionChecker(player, borad, cureentPiecesDirection, newPiecesDirection, newSecondDirection, firstPiece, allayPieces);
                // handle for block for future use
                player->piecesBlock++;
                player->pieces[firstPiece].piecesBlock = 2;
                player->pieces[allayPieces[0]].piecesBlock = 2;
                player->pieces[allayPieces[1]].piecesBlock = 2;
                // print what happend
                printf("%c pieces %d teleport to Kotuwa cell->(%d) make a super bolck with %d pieces and %d pieces and that teleport pieces not efficted anything\n", player->playercolor, firstPiece, KotuwaCell, allayPieces[0], allayPieces[1]);
                // assing  new position to pieces
                player->pieces[firstPiece].piecesPosition = KotuwaCell;
                pieces[cureentplayer][allayPieces[0]] = player->pieces[allayPieces[0]].piecesPosition;
                pieces[cureentplayer][allayPieces[1]] = player->pieces[allayPieces[1]].piecesPosition;
                pieces[cureentplayer][firstPiece] = player->pieces[firstPiece].piecesPosition;
            }
            if (newPositionAllayPlayerPieces == 3)
            {
                printf("%c pieces can't teleport Kotuwa cell->(%d) allay block %d pieces , %d pieces and %d pieces\n", player->playercolor, firstPiece, KotuwaCell, allayPieces[0], allayPieces[1], allayPieces[2]);
            }
            if (newPositionEnemyPlayerPieces == 0)
            {
                printf("%c pieces %d teleport to Kotuwa Cell->(%d) capture %c player %d pieces so that teleport piece not efficted anything\n", player->playercolor, firstPiece, KotuwaCell, player[enemyPlayer].playercolor, enemyPieces[0]);
                player->pieces[firstPiece].piecesPosition = KotuwaCell;
                pieces[cureentplayer][firstPiece] = player->pieces[firstPiece].piecesPosition;
                player->pieces[firstPiece].piecesCaptured = 1;
                piecesCaptured(enemyPlayer, enemyPieces[0], 0, 0, player, borad);
            }
            if (newPositionEnemyPlayerPieces > 0)
            {
                printf("%c player %d piece can't move to Kotuwa cell->(%d) because it block by enemy block\n", player->playercolor, firstPiece, KotuwaCell);
            }
            if (newPositionAllayPlayerPieces == 0)
            {
                player->pieces[firstPiece].piecesPosition = KotuwaCell;
                player->pieces[firstPiece].mystryCellTurns = 4;
                player->pieces[firstPiece].turnSkkiped = 1;
                printf("Next four rounds will be skipped for player %c pieces %d\n", player->playercolor, firstPiece);
            }
        }
    }
}
void playerCall(Player *player,Borad *borad,int playerNum,int*piecesToHome,int rollNum,int (*piecesNum[3]))
{
if (player[playerNum].playercolor=='G')
    {
        greenplayer(&player[playerNum],borad,playerNum,rollNum,&(*piecesToHome),piecesNum);
    }
if (player[playerNum].playercolor=='R')
    {
        redplayer(&player[playerNum],borad,playerNum,rollNum,&(*piecesToHome),piecesNum);
    }
    if (player[playerNum].playercolor=='Y')
    {
        yellowplayer(&player[playerNum],borad,playerNum,rollNum,&(*piecesToHome),piecesNum);
    }
if (player[playerNum].playercolor=='B')
    {
        blueplayer(&player[playerNum],borad,playerNum,rollNum,&(*piecesToHome),piecesNum);
    }
}

void greenplayer(Player *player, Borad *borad, int playerNum, int rollNum, int *piecesToHome, int (*piecesNum[3]))

{
    int allayPieces[3] = {-1, -1, -1};
    int allayPieces1[3] = {-1, -1, -1};
    int enemyPieces[3] = {-1, -1, -1};
    int enemyPlayer = 0;
    int num=-1;

    if (rollNum == 6)
    {
        for (int i = 0; i < numPlayers; i++)
        {
            if (player->pieces[i].piecesPosition == base) // not home in base

            {
                *piecesNum[0] = i;
                *piecesToHome = 1;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (player->pieces[i].piecesDirection == 1)
        {

            for (int j = 0; j < 4; j++)
            {
                if (i != j && player->pieces[i].piecesPosition + rollNum == player->pieces[j].piecesPosition)
                {
                    int position = player->pieces[i].piecesPosition;

                    int currentPiecesPosition = countAllyPiecesAtPosition(position, playerNum, &allayPieces, &i);
                    if (currentPiecesPosition == 1)
                    {
                        *piecesToHome = 2;
                        *piecesNum[0] = i;
                    }
                    if (currentPiecesPosition == 2)
                    {
                        *piecesToHome = 3;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                    }
                }
                int newPosition = player->pieces[i].piecesPosition + rollNum;
                int newPosition1 = player->pieces[i].piecesPosition + (rollNum / 2);
                int newPosition2 = player->pieces[i].piecesPosition + (rollNum / 3);
                int prePosition = player->pieces[i].piecesPosition;
                int enemyPiecesPosition = countEnemyPiecesAtPosition(newPosition, playerNum, &enemyPlayer, &enemyPieces);
                int enemyPiecesPosition1 = countEnemyPiecesAtPosition(newPosition1, playerNum, &enemyPlayer, &enemyPieces);
                int enemyPiecesPosition2 = countEnemyPiecesAtPosition(newPosition2, playerNum, &enemyPlayer, &enemyPieces);
                int currentPiecesPosition = countAllyPiecesAtPosition(prePosition, playerNum, &allayPieces, &i);
                // capture area
                if (enemyPiecesPosition == 1)
                {
                    switch (currentPiecesPosition)
                    {
                    case 1:
                        *piecesToHome = 5;
                        *piecesNum[0] = i;
                        break;
                    case 2:
                        *piecesToHome = 6;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        break;
                    case 3:
                        *piecesToHome = 7;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        *piecesNum[2] = allayPieces[1];

                        break;
                    default:
                        break;
                    }
                }
                if (enemyPiecesPosition == 2)
                {
                    switch (currentPiecesPosition)
                    {
                    case 2:
                        *piecesToHome = 6;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        break;
                    case 3:
                        *piecesToHome = 7;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        *piecesNum[2] = allayPieces[1];

                        break;
                    default:
                        break;
                    }
                }
                if (enemyPiecesPosition == 3)
                {
                    switch (currentPiecesPosition)
                    {
                    case 3:
                        *piecesToHome = 7;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        *piecesNum[2] = allayPieces[1];

                        break;
                    default:
                        break;
                    }
                }
                // mystry cell
                if (borad[newPosition].mysteryCell == 1 && currentPiecesPosition == 1)
                {
                    *piecesNum[0] = i;
                    *piecesToHome = 8;
                }
                //block breaker
                int currentPiecesPosition1 = countAllyPiecesAtPosition(newPosition1, playerNum, &allayPieces1,&num);
                if (currentPiecesPosition1==2)
                {
                    if (currentPiecesPosition==2)
                    {
                        blockBreaker(player,borad,playerNum,allayPieces[0],allayPieces[1],-1);
                        *piecesNum[0]=allayPieces[0];
                        *piecesToHome=10;

                    }
                    
                }
                if (currentPiecesPosition==2)
                {
                    if (enemyPiecesPosition1==3)
                    {
                        blockBreaker(player,borad,playerNum,allayPieces[0],allayPieces[1],-1);
                        *piecesNum[0]=allayPieces[0];
                        *piecesToHome=10;
                    }
                    
                }

                
            }
        }
    }
}
void yellowplayer(Player *player, Borad *borad, int playerNum, int rollNum, int *piecesToHome, int (*piecesNum[3]))

{
    int allayPieces[3] = {-1, -1, -1};
    int allayPieces1[3] = {-1, -1, -1};
    int enemyPieces[3] = {-1, -1, -1};
    int enemyPlayer = 0;
    int num=-1;

    if (rollNum == 6)
    {
        for (int i = 0; i < numPlayers; i++)
        {
            if (player->pieces[i].piecesPosition == base) // not home in base

            {
                *piecesNum[0] = i;
                *piecesToHome = 1;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (player->pieces[i].piecesDirection == 1)
        {

            for (int j = 0; j < 4; j++)
            {
                if (i != j && player->pieces[i].piecesPosition + rollNum == player->pieces[j].piecesPosition)
                {
                    int position = player->pieces[i].piecesPosition;

                    int currentPiecesPosition = countAllyPiecesAtPosition(position, playerNum, &allayPieces, &i);
                    if (currentPiecesPosition == 1)
                    {
                        *piecesToHome = 2;
                        *piecesNum[0] = i;
                    }
                    if (currentPiecesPosition == 2)
                    {
                        *piecesToHome = 3;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                    }
                }
                int newPosition = player->pieces[i].piecesPosition + rollNum;
                int newPosition1 = player->pieces[i].piecesPosition + (rollNum / 2);
                int newPosition2 = player->pieces[i].piecesPosition + (rollNum / 3);
                int prePosition = player->pieces[i].piecesPosition;
                int enemyPiecesPosition = countEnemyPiecesAtPosition(newPosition, playerNum, &enemyPlayer, &enemyPieces);
                int enemyPiecesPosition1 = countEnemyPiecesAtPosition(newPosition1, playerNum, &enemyPlayer, &enemyPieces);
                int enemyPiecesPosition2 = countEnemyPiecesAtPosition(newPosition2, playerNum, &enemyPlayer, &enemyPieces);
                int currentPiecesPosition = countAllyPiecesAtPosition(prePosition, playerNum, &allayPieces, &i);
                // capture area
                if (enemyPiecesPosition == 1)
                {
                    switch (currentPiecesPosition)
                    {
                    case 1:
                        *piecesToHome = 5;
                        *piecesNum[0] = i;
                        break;
                    case 2:
                        *piecesToHome = 6;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        break;
                    case 3:
                        *piecesToHome = 7;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        *piecesNum[2] = allayPieces[1];

                        break;
                    default:
                        break;
                    }
                }
                if (enemyPiecesPosition == 2)
                {
                    switch (currentPiecesPosition)
                    {
                    case 2:
                        *piecesToHome = 6;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        break;
                    case 3:
                        *piecesToHome = 7;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        *piecesNum[2] = allayPieces[1];

                        break;
                    default:
                        break;
                    }
                }
                if (enemyPiecesPosition == 3)
                {
                    switch (currentPiecesPosition)
                    {
                    case 3:
                        *piecesToHome = 7;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        *piecesNum[2] = allayPieces[1];

                        break;
                    default:
                        break;
                    }
                }
                // mystry cell
                if (borad[newPosition].mysteryCell == 1 && currentPiecesPosition == 1)
                {
                    *piecesNum[0] = i;
                    *piecesToHome = 8;
                }
                //block breaker
                int currentPiecesPosition1 = countAllyPiecesAtPosition(newPosition1, playerNum, &allayPieces1,&num);
                if (currentPiecesPosition1==2)
                {
                    if (currentPiecesPosition==2)
                    {
                        blockBreaker(player,borad,playerNum,allayPieces[0],allayPieces[1],-1);
                        *piecesNum[0]=allayPieces[0];
                        *piecesToHome=10;

                    }
                    
                }
                if (currentPiecesPosition==2)
                {
                    if (enemyPiecesPosition1==3)
                    {
                        blockBreaker(player,borad,playerNum,allayPieces[0],allayPieces[1],-1);
                        *piecesNum[0]=allayPieces[0];
                        *piecesToHome=10;
                    }
                    
                }

                
            }
        }
    }
}
void redplayer(Player *player, Borad *borad, int playerNum, int rollNum, int *piecesToHome, int (*piecesNum[3]))

{
    int allayPieces[3] = {-1, -1, -1};
    int allayPieces1[3] = {-1, -1, -1};
    int enemyPieces[3] = {-1, -1, -1};
    int enemyPlayer = 0;
    int num=-1;

    if (rollNum == 6)
    {
        for (int i = 0; i < numPlayers; i++)
        {
            if (player->pieces[i].piecesPosition == base) // not home in base

            {
                *piecesNum[0] = i;
                *piecesToHome = 1;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (player->pieces[i].piecesDirection == 1)
        {

            for (int j = 0; j < 4; j++)
            {
                if (i != j && player->pieces[i].piecesPosition + rollNum == player->pieces[j].piecesPosition)
                {
                    int position = player->pieces[i].piecesPosition;

                    int currentPiecesPosition = countAllyPiecesAtPosition(position, playerNum, &allayPieces, &i);
                    if (currentPiecesPosition == 1)
                    {
                        *piecesToHome = 2;
                        *piecesNum[0] = i;
                    }
                    if (currentPiecesPosition == 2)
                    {
                        *piecesToHome = 3;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                    }
                }
                int newPosition = player->pieces[i].piecesPosition + rollNum;
                int newPosition1 = player->pieces[i].piecesPosition + (rollNum / 2);
                int newPosition2 = player->pieces[i].piecesPosition + (rollNum / 3);
                int prePosition = player->pieces[i].piecesPosition;
                int enemyPiecesPosition = countEnemyPiecesAtPosition(newPosition, playerNum, &enemyPlayer, &enemyPieces);
                int enemyPiecesPosition1 = countEnemyPiecesAtPosition(newPosition1, playerNum, &enemyPlayer, &enemyPieces);
                int enemyPiecesPosition2 = countEnemyPiecesAtPosition(newPosition2, playerNum, &enemyPlayer, &enemyPieces);
                int currentPiecesPosition = countAllyPiecesAtPosition(prePosition, playerNum, &allayPieces, &i);
                // capture area
                if (enemyPiecesPosition == 1)
                {
                    switch (currentPiecesPosition)
                    {
                    case 1:
                        *piecesToHome = 5;
                        *piecesNum[0] = i;
                        break;
                    case 2:
                        *piecesToHome = 6;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        break;
                    case 3:
                        *piecesToHome = 7;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        *piecesNum[2] = allayPieces[1];

                        break;
                    default:
                        break;
                    }
                }
                if (enemyPiecesPosition == 2)
                {
                    switch (currentPiecesPosition)
                    {
                    case 2:
                        *piecesToHome = 6;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        break;
                    case 3:
                        *piecesToHome = 7;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        *piecesNum[2] = allayPieces[1];

                        break;
                    default:
                        break;
                    }
                }
                if (enemyPiecesPosition == 3)
                {
                    switch (currentPiecesPosition)
                    {
                    case 3:
                        *piecesToHome = 7;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        *piecesNum[2] = allayPieces[1];

                        break;
                    default:
                        break;
                    }
                }
                // mystry cell
                if (borad[newPosition].mysteryCell == 1 && currentPiecesPosition == 1)
                {
                    *piecesNum[0] = i;
                    *piecesToHome = 8;
                }
                //block breaker
                int currentPiecesPosition1 = countAllyPiecesAtPosition(newPosition1, playerNum, &allayPieces1,&num);
                if (currentPiecesPosition1==2)
                {
                    if (currentPiecesPosition==2)
                    {
                        blockBreaker(player,borad,playerNum,allayPieces[0],allayPieces[1],-1);
                        *piecesNum[0]=allayPieces[0];
                        *piecesToHome=10;

                    }
                    
                }
                if (currentPiecesPosition==2)
                {
                    if (enemyPiecesPosition1==3)
                    {
                        blockBreaker(player,borad,playerNum,allayPieces[0],allayPieces[1],-1);
                        *piecesNum[0]=allayPieces[0];
                        *piecesToHome=10;
                    }
                    
                }

                
            }
        }
    }
}
void blueplayer(Player *player, Borad *borad, int playerNum, int rollNum, int *piecesToHome, int (*piecesNum[3]))

{
    int allayPieces[3] = {-1, -1, -1};
    int allayPieces1[3] = {-1, -1, -1};
    int enemyPieces[3] = {-1, -1, -1};
    int enemyPlayer = 0;
    int num=-1;

    if (rollNum == 6)
    {
        for (int i = 0; i < numPlayers; i++)
        {
            if (player->pieces[i].piecesPosition == base) // not home in base

            {
                *piecesNum[0] = i;
                *piecesToHome = 1;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (player->pieces[i].piecesDirection == 1)
        {

            for (int j = 0; j < 4; j++)
            {
                if (i != j && player->pieces[i].piecesPosition + rollNum == player->pieces[j].piecesPosition)
                {
                    int position = player->pieces[i].piecesPosition;

                    int currentPiecesPosition = countAllyPiecesAtPosition(position, playerNum, &allayPieces, &i);
                    if (currentPiecesPosition == 1)
                    {
                        *piecesToHome = 2;
                        *piecesNum[0] = i;
                    }
                    if (currentPiecesPosition == 2)
                    {
                        *piecesToHome = 3;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                    }
                }
                int newPosition = player->pieces[i].piecesPosition + rollNum;
                int newPosition1 = player->pieces[i].piecesPosition + (rollNum / 2);
                int newPosition2 = player->pieces[i].piecesPosition + (rollNum / 3);
                int prePosition = player->pieces[i].piecesPosition;
                int enemyPiecesPosition = countEnemyPiecesAtPosition(newPosition, playerNum, &enemyPlayer, &enemyPieces);
                int enemyPiecesPosition1 = countEnemyPiecesAtPosition(newPosition1, playerNum, &enemyPlayer, &enemyPieces);
                int enemyPiecesPosition2 = countEnemyPiecesAtPosition(newPosition2, playerNum, &enemyPlayer, &enemyPieces);
                int currentPiecesPosition = countAllyPiecesAtPosition(prePosition, playerNum, &allayPieces, &i);
                // capture area
                if (enemyPiecesPosition == 1)
                {
                    switch (currentPiecesPosition)
                    {
                    case 1:
                        *piecesToHome = 5;
                        *piecesNum[0] = i;
                        break;
                    case 2:
                        *piecesToHome = 6;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        break;
                    case 3:
                        *piecesToHome = 7;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        *piecesNum[2] = allayPieces[1];

                        break;
                    default:
                        break;
                    }
                }
                if (enemyPiecesPosition == 2)
                {
                    switch (currentPiecesPosition)
                    {
                    case 2:
                        *piecesToHome = 6;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        break;
                    case 3:
                        *piecesToHome = 7;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        *piecesNum[2] = allayPieces[1];

                        break;
                    default:
                        break;
                    }
                }
                if (enemyPiecesPosition == 3)
                {
                    switch (currentPiecesPosition)
                    {
                    case 3:
                        *piecesToHome = 7;
                        *piecesNum[0] = i;
                        *piecesNum[1] = allayPieces[0];
                        *piecesNum[2] = allayPieces[1];

                        break;
                    default:
                        break;
                    }
                }
                // mystry cell
                if (borad[newPosition].mysteryCell == 1 && currentPiecesPosition == 1)
                {
                    *piecesNum[0] = i;
                    *piecesToHome = 8;
                }
                //block breaker
                int currentPiecesPosition1 = countAllyPiecesAtPosition(newPosition1, playerNum, &allayPieces1,&num);
                if (currentPiecesPosition1==2)
                {
                    if (currentPiecesPosition==2)
                    {
                        blockBreaker(player,borad,playerNum,allayPieces[0],allayPieces[1],-1);
                        *piecesNum[0]=allayPieces[0];
                        *piecesToHome=10;

                    }
                    
                }
                if (currentPiecesPosition==2)
                {
                    if (enemyPiecesPosition1==3)
                    {
                        blockBreaker(player,borad,playerNum,allayPieces[0],allayPieces[1],-1);
                        *piecesNum[0]=allayPieces[0];
                        *piecesToHome=10;
                    }
                    
                }

                
            }
        }
    }
}
