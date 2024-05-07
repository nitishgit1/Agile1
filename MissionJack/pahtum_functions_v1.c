#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 7

void printBoard(char board[SIZE][SIZE]);
bool isValidMove(char board[SIZE][SIZE], int row, int col);
void playMove(char board[SIZE][SIZE], char player, int *x, int *y);
void initializeBoard(char board[SIZE][SIZE]);
void scoreBoard(char board[SIZE][SIZE], int countX[5], int countO[5]);
void printScores(int countX[5], int countO[5]);
void playGame(char board[SIZE][SIZE], char player1, char player2);

// Function to print the board with ASCII graphics
void printBoard(char board[SIZE][SIZE]) {
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
    return (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ');
}

// Function to play a move
void playMove(char board[SIZE][SIZE], char player, int *x, int *y) {
    int row, col;
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (!isValidMove(board, row, col));
    
    *x = row;
    *y = col;
}


void initializeBoard(char board[SIZE][SIZE])
{
    // Initialize the board
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void runUnitTests() {
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

// Function to score the board and show breakdown of scores
void scoreBoard(char board[SIZE][SIZE], int countX[5], int countO[5]) 
{
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

void printScores(int countX[5], int countO[5])
{
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

void playGame(char board[SIZE][SIZE], char player1, char player2)
{
    char currentPlayer = player1;
    int moves = 0;

    // Initialize the board
    initializeBoard(board);    
    int countX[5], countO[5];

    // Main game loop
    int row = -1, col = -1;
    while (moves < SIZE * SIZE) 
    {
        printf("\nCurrent Board:\n");
        printBoard(board);
        scoreBoard(board, countX, countO);
        printScores(countX, countO);
        row = -1;
        col = -1;
        playMove(board, currentPlayer, &row, &col);
        if(isValidMove(board, row, col))
	  {
    	board[row][col] = currentPlayer;
  	}
        currentPlayer = (currentPlayer == player1) ? player2 : player1; // Switch player
        moves++;
    }
}

/*
int main() {
    srand(time(NULL)); // Seed the random number generator
    
    // Run unit tests
    runUnitTests();
    
    char board[SIZE][SIZE], player1 = 'X', player2 = 'O';
    
    playGame(board, player1, player2);

	printf("\nFinal Board: \n");
	printBoard(board);
	
	int countX[5], countO[5];
	scoreBoard(board, countX, countO);
	printScores(countX, countO);
 
}
*/

