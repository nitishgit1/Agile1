#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 7

// Function to print the board with colored cells (from code 1)
void printBoard(char board[SIZE][SIZE]) {
    // Print column numbers
    printf("  ");
    for (int col = 0; col < SIZE; col++) {
        printf(" %d ", col);
    }
    printf("\n");

    // Print top border
    printf("  ");
    for (int col = 0; col < SIZE * 4 + 1; col++) {
        printf("-");
    }
    printf("\n");

    for (int row = 0; row < SIZE; row++) {
        // Print row numbers
        printf("%d |", row);
        for (int col = 0; col < SIZE; col++) {
            // Set background color based on cell content
            if (board[row][col] == 'X') {
                printf("\033[0;41m\033[1;30m"); // Background color: red, Text color: black
            } else if (board[row][col] == 'O') {
                printf("\033[0;42m\033[1;30m"); // Background color: green, Text color: black
            } else {
                printf("\033[0;47m\033[1;30m"); // Background color: white, Text color: black
            }
            printf(" %c ", board[row][col]);
            printf("\033[0m"); // Reset colors
            printf("|");
        }
        printf("\n");

        // Print inner border
        printf("  ");
        for (int col = 0; col < SIZE; col++) {
            printf("----");
        }
        printf("\n");
    }
}

// Function to check if a move is valid (from code 2)
bool isValidMove(char board[SIZE][SIZE], int row, int col) {
    return (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ');
}

// Function to play a move (from code 2)
void playMove(char board[SIZE][SIZE], char player, int *x, int *y) {
    int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!isValidMove(board, row, col));

    *x = row;
    *y = col;
}

// Function to initialize the board (from code 2)
void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to score the board (from code 2)
void scoreBoard(char board[SIZE][SIZE], int countX[5], int countO[5]) {
    // ... (implementation from code 2)
}

// Function to print scores (from code 2)
void printScores(int countX[5], int countO[5]) {
    // ... (implementation from code 2)
}

// Function to play the game (modified from code 2)
void playGame(char board[SIZE][SIZE], char player1, char player2) {
    char currentPlayer = player1;
    int moves = 0;

    // Initialize the board
    initializeBoard(board);    

    // Main game loop
    int row = -1, col = -1;
    while (moves < SIZE * SIZE) {
        printf("\nCurrent Board:\n");
        printBoard(board); // Use the colored board printing function
        row = -1;
        col = -1;
        playMove(board, currentPlayer, &row, &col);
        if (isValidMove(board, row, col)) {
            board[row][col] = currentPlayer;
        }
        currentPlayer = (currentPlayer == player1) ? player2 : player1; // Switch player
        moves++;
    }
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    // ... (Unit tests from code 2)

    char board[SIZE][SIZE], player1 = 'X', player2 = 'O';

    playGame(board, player1, player2);

    printf("\nFinal Board: \n");
    printBoard(board); // Use the colored board printing function

    int countX[5], countY[5];
    scoreBoard(board, countX, countY);
    printScores(countX, countY);

}