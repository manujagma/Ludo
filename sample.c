#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HOME -1
#define START_POINT 0
#define NUM_PLAYERS 4
#define BOARD_SIZE 51
#define GREEN_HOME 0  // Placeholder value for green home

typedef struct {
    int piecesPosition;
    int startgame;
} Pieces;

typedef struct {
    Pieces pieces[4];
    char playerColor;
    int startGamePieces;
} Player;

typedef struct {
    int boardNum;
    int piecesNum;
} Board;

// Function prototypes
int roll();
void initializePlayers(Player *players);
void initializeBoard(Board *board);
int determineStartingPlayer();
void playermove(Player *players, Board *board, int playerNum);
void playerAiMove(Player *players, Board *board, int playerNum);
void printPlayers(const Player *players);
int canMoveToPosition(Player *player, int pieceIndex, int rollNum);
int canCreateBlock(Player *player, int pieceIndex, int rollNum, Board *board);
int shouldBreakBlock(Player *player, int pieceIndex, int rollNum, Board *board);

int main() {
    srand(time(NULL));

    Player players[NUM_PLAYERS];
    Board board[BOARD_SIZE];

    initializePlayers(players);
    initializeBoard(board);

    int startPlayer = determineStartingPlayer();
    printf("Starting Player: %d\n", startPlayer);

    printPlayers(players);

    // Example game loop (simplified)
    while (1) {
        for (int i = 0; i < NUM_PLAYERS; i++) {
            if (players[i].playerColor == 'G') {  // Example condition for AI player
                playerAiMove(players, board, i);
            } else {
                playermove(players, board, i);
            }
        }
        // Add conditions to break the loop based on game end conditions
    }

    return 0;
}

int roll() {
    return (rand() % 6) + 1;
}

void initializePlayers(Player *players) {
    char colors[] = {'R', 'G', 'Y', 'B'};
    for (int i = 0; i < NUM_PLAYERS; i++) {
        players[i].playerColor = colors[i];
        players[i].startGamePieces = 0;
        for (int j = 0; j < 4; j++) {
            players[i].pieces[j].piecesPosition = HOME;
            players[i].pieces[j].startgame = -1;
        }
    }
}

void initializeBoard(Board *board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i].boardNum = i;
        board[i].piecesNum = 0;
    }
}

int determineStartingPlayer() {
    int rolls[NUM_PLAYERS];
    int highestRoll = 0;
    int startPlayer = 0;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        rolls[i] = roll();
        if (rolls[i] > highestRoll) {
            highestRoll = rolls[i];
            startPlayer = i;
        }
    }

    return startPlayer;
}

void playermove(Player *players, Board *board, int playerNum) {
    int rollNum = roll();
    Player *currentPlayer = &players[playerNum];
    printf("Player %c rolled a %d\n", currentPlayer->playerColor, rollNum);

    // Example movement logic
    for (int i = 0; i < 4; i++) {
        if (currentPlayer->pieces[i].piecesPosition != HOME) {
            int newPosition = (currentPlayer->pieces[i].piecesPosition + rollNum) % BOARD_SIZE;
            board[currentPlayer->pieces[i].piecesPosition].piecesNum--;
            currentPlayer->pieces[i].piecesPosition = newPosition;
            board[newPosition].piecesNum++;
            break;
        }
    }
}

void playerAiMove(Player *players, Board *board, int playerNum) {
    Player *currentPlayer = &players[playerNum];
    int rollNum = roll();
    printf("AI Player %c rolled a %d\n", currentPlayer->playerColor, rollNum);

    if (currentPlayer->playerColor != 'G') {
        playermove(players, board, playerNum);  // Placeholder for other AI logic
        return;
    }

    // Logic for green player
    if (rollNum == 6) {
        for (int i = 0; i < 4; i++) {
            if (currentPlayer->pieces[i].piecesPosition == HOME) {
                // Move piece out of home if possible
                currentPlayer->pieces[i].piecesPosition = GREEN_HOME;
                board[GREEN_HOME].piecesNum++;
                return;
            }
        }
    }

    // Prioritize moving pieces home or creating blocks
    for (int i = 0; i < 4; i++) {
        if (canMoveToPosition(currentPlayer, i, rollNum)) {
            int newPosition = (currentPlayer->pieces[i].piecesPosition + rollNum) % BOARD_SIZE;
            board[currentPlayer->pieces[i].piecesPosition].piecesNum--;
            currentPlayer->pieces[i].piecesPosition = newPosition;
            board[newPosition].piecesNum++;
            return;
        }
    }

    // Check for block breaking
    for (int i = 0; i < 4; i++) {
        if (shouldBreakBlock(currentPlayer, i, rollNum, board)) {
            int newPosition = (currentPlayer->pieces[i].piecesPosition + rollNum) % BOARD_SIZE;
            board[currentPlayer->pieces[i].piecesPosition].piecesNum--;
            currentPlayer->pieces[i].piecesPosition = newPosition;
            board[newPosition].piecesNum++;
            return;
        }
    }
}

int canMoveToPosition(Player *player, int pieceIndex, int rollNum) {
    int newPosition = player->pieces[pieceIndex].piecesPosition + rollNum;
    if (newPosition >= BOARD_SIZE) {
        newPosition %= BOARD_SIZE;
    }
    // Add any additional rules for moving to this position
    return player->pieces[pieceIndex].piecesPosition != HOME;
}

int canCreateBlock(Player *player, int pieceIndex, int rollNum, Board *board) {
    int newPosition = player->pieces[pieceIndex].piecesPosition + rollNum;
    if (newPosition >= BOARD_SIZE) {
        newPosition %= BOARD_SIZE;
    }
    // Check if moving to this position creates a block
    return board[newPosition].piecesNum > 1;
}

int shouldBreakBlock(Player *player, int pieceIndex, int rollNum, Board *board) {
    int newPosition = player->pieces[pieceIndex].piecesPosition + rollNum;
    if (newPosition >= BOARD_SIZE) {
        newPosition %= BOARD_SIZE;
    }
    // Check if breaking a block is necessary
    for (int i = 0; i < 4; i++) {
        if (player->pieces[i].piecesPosition != HOME && i != pieceIndex) {
            int forwardPosition = player->pieces[i].piecesPosition + rollNum;
            if (forwardPosition >= BOARD_SIZE) {
                forwardPosition %= BOARD_SIZE;
            }
            if (board[forwardPosition].piecesNum == 0) {
                return 0;  // Another piece can move forward without breaking the block
            }
        }
    }
    return 1;
}

void printPlayers(const Player *players) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %d (Color: %c):\n", i + 1, players[i].playerColor);
        for (int j = 0; j < 4; j++) {
            printf("  Piece %d: Position = %d, StartGame = %d\n",
                   j + 1, players[i].pieces[j].piecesPosition, players[i].pieces[j].startgame);
        }
    }
}
