#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define home -1
#define startPoint 0
#define numPlayers 4
//player pieces
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
}Player;
// Call random numbers 
int roll()
{
    return (rand()%6)+1;
}
//functions
void playermove();
int playerstart();
void playerInstall();



int main()
{
    Player player[numPlayers];
    playerInstall(&player);

    
    
}
int playerstart()
{
    int rollNum =roll();
    

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
void playermove()
{

}