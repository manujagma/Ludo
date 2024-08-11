#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 52  // Standard Ludo board size
#define START_POSITION 0
#define NUM_PLAYERS 4

typedef struct {
    int position;
    int hasStarted;
} Player;

// Function to roll a dice
int rollDice() {
    return (rand() % 6) + 1;
}

// Function to move a player's token
void movePlayer(Player* player, int roll) {
    if (!player->hasStarted) {
        if (roll == 6) {
            player->hasStarted = 1;
            player->position = START_POSITION + 1;
            printf("Player starts moving! New position: %d\n", player->position);
        } else {
            printf("Player needs a 6 to start. Roll was: %d\n", roll);
        }
    } else {
        player->position += roll;
        if (player->position > BOARD_SIZE) {
            player->position = BOARD_SIZE;  // Ensuring the position doesn't exceed the board size
        }
        printf("Player moves by %d. New position: %d\n", roll, player->position);
    }
}

int main() {
    srand(time(NULL));  // Seed for random number generation

    Player players[NUM_PLAYERS];  // Array to hold the 4 players
    for (int i = 0; i < NUM_PLAYERS; i++) {
        players[i].position = 0;
        players[i].hasStarted = 0;
    }

    int currentPlayer = 0;

    for (int i = 0; i < 20; i++) {  // Simulate 20 moves
        int roll = rollDice();
        printf("Player %d's turn. Dice roll: %d\n", currentPlayer + 1, roll);
        movePlayer(&players[currentPlayer], roll);

        // Move to the next player
        currentPlayer = (currentPlayer + 1) % NUM_PLAYERS;
    }

    return 0;
}
