#include <stdio.h>

#define NUM_PLAYERS 4
#define NUM_PIECES 4

int countPiecesAtPosition(int position, int currentPlayer, int *enemyIndex, int pieces[NUM_PLAYERS][NUM_PIECES]) {
    int count = 0;
    int firstPlayerIndex = -1;

    // Iterate over all players and their pieces
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < NUM_PIECES; j++) {
            if (pieces[i][j] == position) {
                printf("Player %d's piece %d is at position %d\n", i + 1, j + 1, position);

                if (firstPlayerIndex == -1) {
                    firstPlayerIndex = i;  // Set the first player index who has a piece at this position
                } else if (firstPlayerIndex != i) {
                    *enemyIndex = i;  // If a different player is found, set the enemy index
                }
                count++;
            }
        }
    }

    // Return the count (which will be 1, 2, or 3)
    if (count == 4 || position == 0) {
        return 0;  // Return 0 if four pieces are in the same position, or the position is 0
    }

    return count;
}

void handlePieceMovement(int position, int currentPlayer, int pieces[NUM_PLAYERS][NUM_PIECES]) {
    int enemyIndex = -1;  // Initialize to -1 to indicate no enemy found
    int result = countPiecesAtPosition(position, currentPlayer, &enemyIndex, pieces);

    if (result == 1) {
        printf("Player %d's piece can move freely.\n", currentPlayer + 1);
    } else if (result > 1) {
        if (enemyIndex != -1) {
            printf("Player %d's piece is blocked by enemy pieces.\n", currentPlayer + 1);
        } else {
            printf("Player %d's pieces are blocking themselves at position %d.\n", currentPlayer + 1, position);
        }
    } else {
        printf("No valid pieces at position %d.\n", position);
    }
}

int main() {
    // Example 2D array representing pieces' positions
    int pieces[NUM_PLAYERS][NUM_PIECES] = {
        {10, 20, 30, 10},  // Player 1
        {15, 10, 25, 35},  // Player 2
        {30, 10, 45, 50},  // Player 3
        {10, 20, 30, 40}   // Player 4
    };

    int testPosition = 10;
    int currentPlayer = 0;  // Example: Player 1 is the current player

    handlePieceMovement(testPosition, currentPlayer, pieces);

    return 0;
}
/*void playerAiCall(Player *player,Borad *borad,int num,int *piecesToHome,int rollNum,int currentPlayer)
{
    if (num==1)
    {
        greenplayer(&player,&borad,rollNum,&piecesToHome);
    }

}*/
    /*
    if (player[currentPlayer].playercolor=='G')
    {
        greenplayer(&player[currentPlayer],&borad,rollNum,&picesToHome,&piecesNum);

        if (player[currentPlayer].pieces[*piecesNum].piecesPosition==home && player[currentPlayer].pieces[*piecesNum].startgame==0)
        {
           player[currentPlayer].pieces[*piecesNum].piecesPosition=greenHome;//please assign value
           player[currentPlayer].pieces[*piecesNum].startgame=1;

           borad[greenHome].piecesNum+=4;//green go on 4,8,12
        }





















            //stay in borad size
            if (player[currentPlayer].pieces[*piecesNum].piecesPosition>=Borad_size)
            {
                player[currentPlayer].pieces[*piecesNum].piecesPosition%=Borad_size;
            }

        }*/
for (short i = 0; i < numPlayers; i++)
        {

            int piecesPosition = player->pieces[i].piecesPosition; // player has pieces
            for (short j = 0; j < numPlayers; j++)
            {
                int piecesPosition1 = player[i].pieces[j].piecesPosition; // enemy players pieces

                if (borad[newCurrentPiecesPosition].piecesName == 2)
                {
                }
                if (*picesToHome == 2 && newCurrentPiecesPosition == piecesPosition && rollNum == 1)
                {
                    /* printf("%d from %d to %d, player %s's piece %d makes a block with piece %d\n",
                      previousCurrentPiecesPosition, newCurrentPiecesPosition, piecesPosition,
                         player->playercolor, *piecesNum, piecesPosition);*/
                    rollNum = 0;
                }
            }
        }
         int enemyPieces[3] = {-1, -1, -1};
                 for (int i = 0; i < 4; i++)
        {int countwin=0;
            if(player[playerNum].pieces[i].startgame==0)
            {
                countwin++;
            }
            if (countwin==4)
            {
                printf("%c player win!!!!",player[playerNum].playercolor);
                stop=0;

            }
            
        }