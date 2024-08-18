#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "main.h"
#define home -1
#define startPoint 0
#define numPlayers 4
#define Borad_size 51//player pieces
#define greenHome 0000//please assign value
typedef struct 
{
    int piecesPosition;
    int startgame;
}Pieces;
//player area
typedef struct Player 
{
    Pieces pieces[4];//make 4 for pieces for one player
    char playercolor;
    int startGamePieces;
}Player;
typedef struct Borad
{
    int boradNum;
    int piecesNum;
}Borad;

// Call random numbers 
int roll()
{
    return (rand()%6)+1;
}
//functions
void playermove();
int playerstart();
void playerInstall();
void greenplayer();
void yellowPlayer();
void redPlayer();
void bluePlayer();
void playerAiCall();
void boradconst();
int bolckPieces();


void printPlayers(Player *player) {
    for (int i = 0; i < numPlayers; i++) {
        printf("Player %d (Color: %c):\n", i + 1, player[i].playercolor);
        for (int j = 0; j < 4; j++) {
            printf("  Piece %d: Position = %d, StartGame = %d\n",
                   j + 1, player[i].pieces[j].piecesPosition, player[i].pieces[j].startgame);
        }
    }
}

int main()
{
    srand(time(NULL));
    //install player
    Player player[numPlayers];
    playerInstall(player);
    //make variable for startPlayer
    int startPlayer=-1;
    //install borad
    
    Borad  borad [Borad_size];
    for (int i = 0; i < Borad_size; i++)
    {
        borad[i].boradNum=i;
        borad[i].piecesNum=0;
    }
    playerstart(&startPlayer);
    printf("%d\n",startPlayer);
    //export to header.h (player play method)
    switch (startPlayer)
    {
    case 0:
        player[0].playercolor='R';
        player[1].playercolor='G';
        player[2].playercolor='Y';
        player[3].playercolor='B';
        break;
    case 1:
        player[0].playercolor='G';
        player[1].playercolor='Y';
        player[2].playercolor='B';
        player[3].playercolor='R';
        break;
    case 2:
        player[0].playercolor='Y';
        player[1].playercolor='B';
        player[2].playercolor='R';
        player[3].playercolor='G';
        break;
    case 3:
        player[0].playercolor='B';
        player[1].playercolor='R';
        player[2].playercolor='G';
        player[3].playercolor='Y';
        break;   
    
    default:
        break;
    }
   // 
   
   printPlayers(player);
    
    
    
}
int playerstart(int *startPlayer)
{   
   
    int tie=1;
    while (tie)
    {
        tie=0;
        int a[4];
        for (int i = 0; i < numPlayers; i++)
        {
             int rollNum =roll();
                a[i]=rollNum;
        }
        *startPlayer=0;
        //shrot this 
        if (a[1]<a[0] && a[2]<a[0] && a[3]<a[0])
        {
            *startPlayer =0; tie=0; 
        }
                if (a[0]<a[1] && a[2]<a[1] && a[3]<a[1])
        {
            tie=0; *startPlayer=1;
        }
                        if (a[0]<a[2] && a[1]<a[2] && a[3]<a[2])
        {
            tie=0; *startPlayer=2;
        }
                        if (a[0]<a[3] && a[2]<a[3] && a[1]<a[3])
        {
            tie=0; *startPlayer=3;
        }
        
    }
    


}
void playerInstall(Player *player)
{
    //give name for each player
player[0].playercolor='R';
player[1].playercolor='G';
player[2].playercolor='Y';
player[3].playercolor='B';
for (int  i = 0; i < numPlayers; i++)
{
    for (int  j = 0; j < numPlayers; j++)
    {
        player[i].pieces[j].piecesPosition=home;
        player[i].pieces[j].startgame=-1;
    }
    
}


}
//behewire of board

void boradconst(Player *player,Borad *borad)
{
    int playerNum =player;
    int boradNum =borad;
    int rollNum =0;
    int piecesNum=0;
    int picesToHome=0;//can move pices to home
while (1)
{
    
    rollNum=roll();
   
    if (rollNum==6)
    {
        
        playerAiCall(&player,&borad,playerNum,&picesToHome);
        playermove(&playerNum,&piecesNum,&rollNum,&picesToHome);
        
        

    }
    



    //stay behind of players and borad (go around like circule)
    playerNum=(++playerNum)%numPlayers;
    boradNum=(++boradNum)%Borad_size;
}
}
void playermove(int *playerNum,int *piecesNum,int *rollNum,int *picesToHome)
{
    
     Borad *borad;
     Player *player;
     int currentPlayer=*playerNum;
     

    
    
    
    if (player[currentPlayer].playercolor=='G')
    {
        
        if (picesToHome==1)
        {
           player[currentPlayer].pieces[*piecesNum].piecesPosition=greenHome;//please assign value
           borad[greenHome].piecesNum+=4;//green go on 4,8,12
        }        
        if(picesToHome==2)//clockwise go
        {
        for (int i = 0; i < *rollNum; i++)
        {   int currentPiecesPositition=player[currentPlayer].pieces[*piecesNum].piecesPosition;
            player[currentPlayer].pieces[*piecesNum].piecesPosition=0;//meya palehata enna one
            currentPiecesPositition++;
           int bolckBehewivre = bolckPiceces(&borad,&player,currentPiecesPositition,currentPlayer);
            

            
            
            

            //stay in borad size
            if (player[currentPlayer].pieces[*piecesNum].piecesPosition>=Borad_size)
            {
                player[currentPlayer].pieces[*piecesNum].piecesPosition%=Borad_size;
            }
        
        }
        }
    }
       
    
    }

int bolckPiceces(Borad *borad,Player *player,int currentPiecesPositition,int currentPlayer)
{
    
    if (player[currentPlayer].playercolor=='G' && borad[currentPiecesPositition].piecesNum==8 )
    {
        
        //print two
        return 1;
    }
    if (player[currentPlayer].playercolor=='G' && borad[currentPiecesPositition].piecesNum==12)
    {
        //print three and can't move any pieces to this cell
        return 0;
    }
    if (borad[currentPiecesPositition].piecesNum==8 && player[currentPiecesPositition].playercolor!='G')
    {
        //print green block block your way
        return 0;
    }
    if (borad[currentPiecesPositition].piecesNum==12 && player[currentPiecesPositition].playercolor!='G')
    {
        //print green super block block your way
        return 0;
    }
    
    
    
}
void playerAiCall(Player *player,Borad *borad,int num,int *piecesToHome)
{
    if (num==1)
    {
        greenplayer(&player,&borad,&piecesToHome);
    }
    
}
void greenplayer(Player *player,Borad *borad,int* piecesToHome)
{
    if (*piecesToHome==0)
    {
        int piecesWay= rand()%2+1;
        if (piecesWay==1)
        {
            *piecesToHome==2;//make clock wise dirction
        }else if(piecesWay==2)
        {
            *piecesToHome==3;//make counter clock wise dirction
        }
    }

}