#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 7

// void printBoard(char board[SIZE][SIZE]);
bool isValidMove(char board[SIZE][SIZE], int row, int col);
void playMove_C3po(char board[SIZE][SIZE], int *x, int *y);
// void initializeBoard(char board[SIZE][SIZE]);
void scoreBoard(char board[SIZE][SIZE], int countX[5]);
// void printScores(int countX[5]);
// void playGame(char board[SIZE][SIZE], char player);
// void runUnitTests();

// Function to print the board with colored cells and row/column numbering
// void printBoard(char board[SIZE][SIZE]) {
//     // Print column numbers
//     printf("    ");
//     for (int col = 0; col < SIZE; col++) {
//         printf(" %2d ", col);
//     }
//     printf("\n");

//     // Print top border
//     printf("    ");
//     for (int col = 0; col < SIZE * 4 + 1; col++) {
//         printf("-");
//     }
//     printf("\n");

//     for (int row = 0; row < SIZE; row++) {
//         // Print row number
//         printf("%2d |", row);
//         for (int col = 0; col < SIZE; col++) {
//             // Set background color based on cell content
//             if (board[row][col] == 'X') {
//                 printf("\033[0;41m\033[1;37m"); // Background color: red, Text color: black
//             } else {
//                 printf("\033[0;47m\033[1;30"); // Background color: white, Text color: black
//             }
//             printf(" %c ", board[row][col]);
//             printf("\033[0m"); // Reset colors
//             printf("|");
//         }
//         printf("\n");

//         // Print inner border
//         printf("    ");
//         for (int col = 0; col < SIZE; col++) {
//             printf("----");
//         }
//         printf("\n");
//     }
// }


// Function to check if a move is valid
bool isValidMove(char board[SIZE][SIZE], int row, int col) {
    return (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ');
}

// Function to play a move
void playMove_C3po(char board[SIZE][SIZE], int *x, int *y)
{
    // Checks for winning moves for the current player.
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                
                // Checks if this move leads to a win for the current player.
                int countX[5] = {0};
                scoreBoard(board, countX);
                if (countX[4] > 0) {
                    *x = i;
                    *y = j;
                    return;
                }
                
                // Undo's the move.
                board[i][j] = ' ';
            }
        }
    }

    // Checks for opponent's winning moves to block.
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O'; // Assume opponent's move
                int countO[5] = {0};
                scoreBoard(board, countO);
                if (countO[2] > 0 || countO[3] > 0 || countO[4] > 0) { // If opponent has a sequence of length 2 , 3 or 4, block it
                    *x = i;
                    *y = j;
                    board[i][j] = ' '; // Undo opponent's move
                    return;
                }
                board[i][j] = ' '; // Undo opponent's move
            }
        }
    }

    // If neither winning moves nor blocking moves are available, make a random move.
    int row, col;
    do
    {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!isValidMove(board, row, col));
    *x = row;
    *y = col;
}

// void initializeBoard(char board[SIZE][SIZE]) {
//     // Initialize the board
//     for (int i = 0; i < SIZE; i++) {
//         for (int j = 0; j < SIZE; j++) {
//             board[i][j] = ' ';
//         }
//     }
// }

// void runUnitTests() {
//     char testBoard[SIZE][SIZE];
//     // Initialize the test board
//     initializeBoard(testBoard);

//     // Test 1: Check if isValidMove correctly validates moves
//     printf("Unit Test 1: isValidMove\n");
//     printf("Testing invalid move at (7,7)...\n");
//     if (isValidMove(testBoard, 7, 7))
//         printf("Test failed: (7,7) should be an invalid move.\n");
//     else
//         printf("Test passed!\n");

//     printf("Testing valid move at (3,3)...\n");
//     if (!isValidMove(testBoard, 3, 3))
//         printf("Test failed: (3,3) should be a valid move.\n");
//     else
//         printf("Test passed!\n");

//     // Test 2: Check if playMove correctly plays a move
//     int row = -1, col = -1;
//     printf("\nUnit Test 2: playMove\n");
//     printf("Playing a move for 'X'...\n");
//     playMove(testBoard, &row, &col);
//     if(isValidMove(testBoard, row, col))
//     {
//         testBoard[row][col] = 'X';
//     }
//     else
//     {
//         printf("Invalid Move provided: row = %d, col = %d", row, col);
//     }
//     printf("Current Board:\n");
//     printBoard(testBoard);
// }

// Function to score the board and show breakdown of scores
void scoreBoard(char board[SIZE][SIZE], int countX[5]) {
    // Intialize. To store counts of sequences of lengths 3, 4, 5, 6, and 7
    for(int i = 0; i < 5; i++)
    {
        countX[i] = 0;
    }

    // Check Horizontally
    for (int i = 0; i < SIZE; i++) {
        int countXCurrent = 0;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 'X') {
                countXCurrent++;
            } else {
                if(countXCurrent >= 3)
                {
                    countX[countXCurrent - 3]++; // Increment count for sequence length
                }

                countXCurrent = 0;
            }
        }
        // Final Pass
        if(countXCurrent >= 3)
        {
            countX[countXCurrent - 3]++; // Increment count for sequence length
        }

        countXCurrent = 0;
    }

    // Check Vertically
    for (int j = 0; j < SIZE; j++) {
        int countXCurrent = 0;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] == 'X') {
                countXCurrent++;
            } else {
                if(countXCurrent >= 3)
                {
                    countX[countXCurrent - 3]++; // Increment count for sequence length
                }

                countXCurrent = 0;
            }
        }
        // Final Pass
        if(countXCurrent >= 3)
        {
            countX[countXCurrent - 3]++; // Increment count for sequence length
        }

        countXCurrent = 0;
    }
}

// void printScores(int countX[5]) {
//     int scoreX = 0;

//     // Print breakdown of scores
//     printf("\nBreakdown of Scores:\n");
//     printf("Player X: ");
//     for (int i = 0; i < 5; i++) {
//         printf("%d sequence of %d, ", countX[i], i + 3);
//         int sequencePosition = i + 3;
//         scoreX += countX[i] * ((sequencePosition == 3) ? 3 : (sequencePosition == 4) ? 10 : (sequencePosition == 5) ? 25 : (sequencePosition == 6) ? 56 : 119);
//     }
//     printf("\n");

//     printf("Score for Player X: %d\n", scoreX);
// }

// void playGame(char board[SIZE][SIZE], char player) {
//     int moves = 0;
//     int countX[5];

//     // Initialize the board
//     initializeBoard(board);

//     // Main game loop
//     int row = -1, col = -1;
//     while (moves < SIZE * SIZE) {
//         printf("\nCurrent Board:\n");
//         printBoard(board);
//         row = -1;
//         col = -1;
//         playMove(board, &row, &col);
//         if (isValidMove(board, row, col)) {
//             board[row][col] = 'X';
//         }
//         moves++;
//     }

//     // Game finished, calculate and print scores
//     printf("\nFinal Board: \n");
//     printBoard(board);
//     scoreBoard(board, countX);
//     printScores(countX);
// }


// void main() {
//     srand(time(NULL)); // Seed the random number generator

//     // Run unit tests
//     runUnitTests();

//     char board[SIZE][SIZE], player1 = 'X';

//     playGame(board, player1);

// }
