#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

#define SIZE 7

void printBoard(char board[SIZE][SIZE]);
bool isValidMove(char board[SIZE][SIZE], int row, int col);
void recommendMoveForO(char board[SIZE][SIZE], int *row, int *col); // Function prototype changed
void initializeBoard(char board[SIZE][SIZE]);
void scoreBoard(char board[SIZE][SIZE], int countX[5], int countO[5]);
void printScores(int countX[5], int countO[5]);
void playGame(char board[SIZE][SIZE], char player1, char player2);
int evaluatePosition(char board[SIZE][SIZE], int row, int col);

// Function to print the board with ASCII graphics
void printBoard(char board[SIZE][SIZE]) {
    // Function remains the same
    printf("    ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d   ", i);
    }
    printf("\n");
    	
    printf("  ");
    for (int i = 0; i <= SIZE * 4; i++) {
        printf("-");
    }
    printf("\n");
    
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("  ");
    for (int i = 0; i <= SIZE * 4; i++) {
        printf("-");
    }
    printf("\n");
}

// Function to check if a move is valid
bool isValidMove(char board[SIZE][SIZE], int row, int col) {
    // Function remains the same
    return (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ');

}

void recommendMoveForO(char board[SIZE][SIZE], int *row, int *col) {
    // Use a random approach to find the first valid move
    int tempRow, tempCol;
    do {
        tempRow = rand() % SIZE;
        tempCol = rand() % SIZE;
    } while (!isValidMove(board, tempRow, tempCol));

    *row = tempRow;
    *col = tempCol;
}


void elongateX(char board[SIZE][SIZE], int *row, int *col) {
    int maxScore = INT_MIN;
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (isValidMove(board, i, j)) {
                int score = evaluatePosition(board, i, j);
                if (score > maxScore) {
                    maxScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    // Use the best found move, or fallback to a random move
    if (bestRow != -1 && bestCol != -1) {
        *row = bestRow;
        *col = bestCol;
    } else { // Fallback if no optimal spot is found
        do {
            *row = rand() % SIZE;
            *col = rand() % SIZE;
        } while (!isValidMove(board, *row, *col));
    }
}


int getLineLength(char board[SIZE][SIZE], int row, int col, char player, int dRow, int dCol) {
    int length = 1;  // Start with the current move as part of the sequence
    int r, c;

    // Extend in the positive direction
    r = row + dRow;
    c = col + dCol;
    while (r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == player) {
        length++;
        r += dRow;
        c += dCol;
    }

    // Extend in the negative direction
    r = row - dRow;
    c = col - dCol;
    while (r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == player) {
        length++;
        r -= dRow;
        c -= dCol;
    }

    return length;
}

int evaluatePosition(char board[SIZE][SIZE], int row, int col) {
    int score = 0;
    int lengthX, lengthO;

    // Only check horizontal and vertical directions
    int directions[2][2] = {{0, 1}, {1, 0}};  // Right (horizontal), Down (vertical)

    for (int d = 0; d < 2; d++) {
        lengthX = getLineLength(board, row, col, 'X', directions[d][0], directions[d][1]);
        lengthO = getLineLength(board, row, col, 'O', directions[d][0], directions[d][1]);

        // Score for X should prefer longer sequences
        score += lengthX * lengthX;  

        // Implement strict blocking: Heavily penalize open 'O' lines that can turn into 3 or more
        if (lengthO >= 2) {  // If O has 2 or more in a row/column and space to extend
            score -= lengthO * 100;  // Use a high penalty factor to ensure blocking
        }
    }
    
    return score;
}







void initializeBoard(char board[SIZE][SIZE]) {
    // Function remains the same
    // Initialize the board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void playMove(char board[SIZE][SIZE], char player, int *x, int *y) {
    if (player == 'X') {
        elongateX(board, x, y);  // Ensure this uses the updated evaluatePosition
    } else {
        recommendMoveForO(board, x, y);  // Random or heuristic for O
    }
}


void runUnitTests() {
    // Function remains the same
    char testBoard[SIZE][SIZE];
    // Initialize the test board
    initializeBoard(testBoard);
    
    // Test 1: Check if isValidMove correctly validates moves
    printf("Unit Test 1: isValidMove\n");
    printf("Testing invalid move at (7,7)...\n");
    if (isValidMove(testBoard, 7, 7))
        printf("Test failed: (7,7) should be an invalid move.\n");
    else
        printf("Test passed!\n");

    printf("Testing valid move at (3,3)...\n");
    if (!isValidMove(testBoard, 3, 3))
        printf("Test failed: (3,3) should be a valid move.\n");
    else
        printf("Test passed!\n");

    // Test 2: Check if playMove correctly plays a move
    int row = -1, col = -1;
    printf("\nUnit Test 2: playMove\n");
    printf("Playing a move for 'X'...\n");
    playMove(testBoard, 'X', &row, &col);
    if(isValidMove(testBoard, row, col))
    {
    	testBoard[row][col] = 'X';
    }
    else
    {
    	printf("Invalid Move provided: row = %d, col = %d", row, col);
    }
    printf("Current Board:\n");
    printBoard(testBoard);
    
    row = -1;
    col = -1;
    printf("\nPlaying a move for 'O'...\n");
    playMove(testBoard, 'O', &row, &col);
    if(isValidMove(testBoard, row, col))
    {
    	testBoard[row][col] = 'O';
    }
    else
    {
    	printf("Invalid Move provided: row = %d, col = %d", row, col);
    }
    printf("Current Board:\n");
    printBoard(testBoard);
}

void scoreBoard(char board[SIZE][SIZE], int countX[5], int countO[5]) {
    // Function remains the same
    // Intialize. To store counts of sequences of lengths 3, 4, 5, 6, and 7
    for(int i = 0; i < 5; i++)
    {
    	countX[i] = 0;
    	countO[i] = 0;
    }
    
    // Check Horizontally
    for (int i = 0; i < SIZE; i++) 
    {
        int countXCurrent = 0, countOCurrent = 0;
        for (int j = 0; j < SIZE; j++) 
        {
//            printf("Reading: %c\n", board[i][j]);
            if (board[i][j] == 'X') 
            {
                countXCurrent++;
                
                if(countOCurrent >= 3)
                {
                	countO[countOCurrent - 3]++; // Increment count for sequence length
                }
                
                countOCurrent = 0;
            } 
            else if (board[i][j] == 'O') 
            {
                countOCurrent++;
            
                if(countXCurrent >= 3)
                {
                	countX[countXCurrent - 3]++; // Increment count for sequence length
                }

                countXCurrent = 0;
            } 
            else 
            {
                if(countOCurrent >= 3)
                {
                	countO[countOCurrent - 3]++; // Increment count for sequence length
                }
                else if(countXCurrent >= 3)
                {
                	countX[countXCurrent - 3]++; // Increment count for sequence length
                }
                
                countXCurrent = 0;
                countOCurrent = 0;
            }
        }
        // Final Pass
        if(countOCurrent >= 3)
        {
        	countO[countOCurrent - 3]++; // Increment count for sequence length
        }
        else if(countXCurrent >= 3)
        {
        	countX[countXCurrent - 3]++; // Increment count for sequence length
        }
        
        countXCurrent = 0;
        countOCurrent = 0;
//        printScores(countX, countO);
    }

    // Check Vertically
    for (int j = 0; j < SIZE; j++) 
    {
        int countXCurrent = 0, countOCurrent = 0;
        for (int i = 0; i < SIZE; i++) 
        {
//            printf("Reading: %c\n", board[i][j]);
            if (board[i][j] == 'X') 
            {
                countXCurrent++;
                
                if(countOCurrent >= 3)
                {
                	countO[countOCurrent - 3]++; // Increment count for sequence length
                }
                
                countOCurrent = 0;
            } 
            else if (board[i][j] == 'O') 
            {
                countOCurrent++;
                
                if(countXCurrent >= 3)
                {
                	countX[countXCurrent - 3]++; // Increment count for sequence length
                }
                
                countXCurrent = 0;
            } 
            else 
            {
                if(countOCurrent >= 3)
                {
                	countO[countOCurrent - 3]++; // Increment count for sequence length
                }
                else if(countXCurrent >= 3)
                {
                	countX[countXCurrent - 3]++; // Increment count for sequence length
                }
                
                countXCurrent = 0;
                countOCurrent = 0;
            }
        }
        // Final Pass
        if(countOCurrent >= 3)
        {
        	countO[countOCurrent - 3]++; // Increment count for sequence length
        }
        else if(countXCurrent >= 3)
        {
        	countX[countXCurrent - 3]++; // Increment count for sequence length
        }
        
        countXCurrent = 0;
        countOCurrent = 0;
//        printScores(countX, countO);
    }
}


void printScores(int countX[5], int countO[5]) {
    // Function remains the same
    int scoreX = 0, scoreO = 0;
    
    // Print breakdown of scores
    printf("\nBreakdown of Scores:\n");
    printf("Player X: ");
    for (int i = 0; i < 5; i++) 
    {
        printf("%d sequence of %d, ", countX[i], i + 3);
	  int sequencePosition = i + 3;
        scoreX += countX[i] * ((sequencePosition == 3) ? 3 : (sequencePosition == 4) ? 10 : (sequencePosition == 5) ? 25 : (sequencePosition == 6) ? 56 : 119);
    }
    printf("\n");
    printf("Player O: ");
    for (int i = 0; i < 5; i++) 
    {
        printf("%d sequence of %d, ", countO[i], i + 3);
        int sequencePosition = i + 3;
        scoreO += countO[i] * ((sequencePosition == 3) ? 3 : (sequencePosition == 4) ? 10 : (sequencePosition == 5) ? 25 : (sequencePosition == 6) ? 56 : 119);
    }
    printf("\n");
    
    printf("Score for Player X: %d\n", scoreX);
    printf("Score for Player O: %d\n", scoreO);
}

void playGame(char board[SIZE][SIZE], char player1, char player2) {
    // Function remains the same
    char currentPlayer = player1; // Start with player1 who is 'X'
    int moves = 0;

    // Initialize the board
    initializeBoard(board);

    // Start by placing 'X' at position (3,3)
    if (isValidMove(board, 3, 3)) {
        board[3][3] = player1; // Place 'X' at (3,3)
        moves++; // Increment moves as one move has been made
    } else {
        printf("Failed to place 'X' at the starting position (3,3).\n");
        return; // Early exit if somehow (3,3) is not valid, which should not happen
    }

    // Main game loop
    int row = -1, col = -1;
    while (moves < SIZE * SIZE) {
        printf("\nCurrent Board:\n");
        printBoard(board);
        row = -1;
        col = -1;
        playMove(board, currentPlayer, &row, &col);
        if(isValidMove(board, row, col)) {
            board[row][col] = currentPlayer;
            moves++; // Increment move count after a successful move
        } else {
            printf("Invalid move by %c at (%d, %d)\n", currentPlayer, row, col);
        }
        currentPlayer = (currentPlayer == player1) ? player2 : player1; // Switch player
    }
}


int main() {
    srand(time(NULL)); // Seed the random number generator
    
    // Run unit tests
    runUnitTests();
    
    char board[SIZE][SIZE], player1 = 'X', player2 = 'O';
    
    playGame(board, player1, player2);

    printf("\nFinal Board: \n");
    printBoard(board);

    int countX[5], countY[5];
    scoreBoard(board, countX, countY);
    printScores(countX, countY);

    return 0; // Ensure proper termination of the main function
}
