#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 7
#define INVALID_MOVE_LIMIT 5

// Function to print the board with colored cells and row/column numbering
void printBoard(char board[SIZE][SIZE]) {
    // Print column numbers
    printf("    ");
    for (int col = 0; col < SIZE; col++) {
        printf("  %2d ", col);
    }
    printf("\n");

    // Print top border
    printf("    ");
    for (int col = 0; col < SIZE * 5 + 1; col++) {
        printf("-");
    }
    printf("\n");

    for (int row = 0; row < SIZE; row++) {
        // Print row number and left border
        printf(" %2d |", row);
        for (int col = 0; col < SIZE; col++) {
            // Set background color based on cell content
            if (board[row][col] == 'X') {
                printf("\033[0;41m\033[2;37m"); // Background color: red, Text color: black
            } else if (board[row][col] == 'O') {
                printf("\033[0;42m\033[2;30m"); // Background color: green, Text color: black
            } else {
                printf("\033[1;30m"); // Background color: white, Text color: black
            }
            printf("  %c ", board[row][col]);
            printf("\033[0m"); // Reset colors
            printf("|");
        }
        printf("\n");

        // Print inner border
        printf("    ");
        for (int col = 0; col < SIZE * 5 + 1; col++) {
            printf("-");
        }
        printf("\n");
    }
}

void initializeBoard(char board[SIZE][SIZE])
{
  // Initialize the board
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      board[i][j] = ' ';
    }
  }
}

int main()

{
    char board[SIZE][SIZE];
    //test case 1:
    initializeBoard(board);
    printBoard(board);

//  // Test Case 2: Board with 'X' and 'O'
//     board[0][0] = 'X';
//     board[1][1] = 'O';
//     board[2][2] = 'X';
//     board[3][3] = 'O';
//     printBoard(board);

//        // Test Case 3: Border Test
//     for (int i = 0; i < SIZE; i++) {
//         board[0][i] = 'X';
//         board[i][0] = 'O';
//     }
//     printBoard(board);

//     // Test Case 4: Special Characters Test
//     //The purpose of this code is to create a test case where the border of the game board is filled with a special character ('*'). This can be useful for testing the printBoard function to ensure it correctly displays the board with the expected content and colors, including the special characters along the border.
//     for (int i = 0; i < SIZE; i++) {
//         for (int j = 0; j < SIZE; j++) {
//             if (i == 0 || j == 0 || i == SIZE - 1 || j == SIZE - 1) {
//                 board[i][j] = '*';
//             }
//         }
//     }
//     printBoard(board);

//     // Test Case 5: Mixed Content Test
//     for (int i = 0; i < SIZE; i++) {
//         for (int j = 0; j < SIZE; j++) {
//             if (i % 2 == 0) {
//                 board[i][j] = 'X';
//             } else {
//                 board[i][j] = 'O';
//             }
//         }
//     }
//     printBoard(board);

    // // Test Case 6: Large Board Test
    // //This code doesn't work because 7*7 is expected table so 20*20 or other numbered table gives an error
    // char largeBoard[20][20];
    // initializeBoard(largeBoard);
    // for (int i = 0; i < 20; i++) {
    //     for (int j = 0; j < 20; j++) {
    //         if (i % 2 == 0) {
    //             largeBoard[i][j] = 'X';
    //         } else {
    //             largeBoard[i][j] = 'O';
    //         }
    //     }
    // }
    // printBoard(largeBoard);

//  // Test Case 7: Random Board Test
//     srand(time(NULL));
//     char randomBoard[SIZE][SIZE];
//     initializeBoard(randomBoard);
//     for (int i = 0; i < SIZE; i++) {
//         for (int j = 0; j < SIZE; j++) {
//             if (rand() % 2 == 0) {
//                 randomBoard[i][j] = 'X';
//             } else {
//                 randomBoard[i][j] = 'O';
//             }
//         }
//     }
//     printBoard(randomBoard);

// //Test Case 8: Player moves
// // Player 1 (X) makes a move
// board[2][3] = 'X';
// printBoard(board);

// // Player 2 (O) makes a move
// board[4][1] = 'O';
// printBoard(board);

// Test Case 9: Invalid Move

// Player 1 (X) makes a valid move
board[2][3] = 'X';
printBoard(board);

// Player 2 (O) tries to make an invalid move (outside the board)
board[7][2] = 'O'; // This should be ignored
printBoard(board);

// Player 1 (X) tries to make an invalid move (overwriting an existing mark)
board[2][3] = 'X'; // This should be ignored
printBoard(board);

    return 0;
    
}