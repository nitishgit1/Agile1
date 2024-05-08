#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

#define SIZE 7

void printBoard(char board[SIZE][SIZE]);
bool isValidMove(char board[SIZE][SIZE], int row, int col);
void playMove(char board[SIZE][SIZE], char player, int *x, int *y);
void initializeBoard(char board[SIZE][SIZE]);
void scoreBoard(char board[SIZE][SIZE], int countX[5], int countO[5], int *scoreX, int *scoreO);
void printScores(int countX[5], int countO[5], int scoreX, int scoreO);
void playGame(char board[SIZE][SIZE], char player1, char player2);
void runUnitTests();

// Function to print the board with colored cells and row/column numbering
void printBoard(char board[SIZE][SIZE])
{
  // Print column numbers
  printf("    ");
  for (int col = 0; col < SIZE; col++)
  {
    printf("  %2d ", col);
  }
  printf("\n");

  // Print top border
  printf("    ");
  for (int col = 0; col < SIZE * 5 + 1; col++)
  {
    printf("-");
  }
  printf("\n");

  for (int row = 0; row < SIZE; row++)
  {
    // Print row number and left border
    printf(" %2d |", row);
    for (int col = 0; col < SIZE; col++)
    {
      // Set background color based on cell content
      if (board[row][col] == 'X')
      {
        printf("\033[0;41m\033[2;37m"); // Background color: red, Text color: black
      }
      else if (board[row][col] == 'O')
      {
        printf("\033[0;42m\033[2;30m"); // Background color: green, Text color: black
      }
      else
      {
        printf("\033[1;30m"); // Background color: white, Text color: black
      }
      printf("  %c ", board[row][col]);
      printf("\033[0m"); // Reset colors
      printf("|");
    }
    printf("\n");

    // Print inner border
    printf("    ");
    for (int col = 0; col < SIZE * 5 + 1; col++)
    {
      printf("-");
    }
    printf("\n");
  }
}

// Function to check if a move is valid
bool isValidMove(char board[SIZE][SIZE], int row, int col)
{
  return (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ');
}

// Function to play a move
void playMove(char board[SIZE][SIZE], char player, int *x, int *y)
{
  int row, col;
  do
  {
    row = rand() % SIZE;
    col = rand() % SIZE;
  } while (!isValidMove(board, row, col));

  *x = row;
  *y = col;
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

void runUnitTests()
{
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
  if (isValidMove(testBoard, row, col))
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
  if (isValidMove(testBoard, row, col))
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
void scoreBoard(char board[SIZE][SIZE], int countX[5], int countO[5], int *scoreX, int *scoreO)
{
  // Initialize to store counts of sequences of lengths 3, 4, 5, 6, and 7
  for (int i = 0; i < 5; i++)
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
      if (board[i][j] == 'X')
      {
        countXCurrent++;

        if (countOCurrent >= 3)
        {
          countO[countOCurrent - 3]++; // Increment count for sequence length
        }

        countOCurrent = 0;
      }
      else if (board[i][j] == 'O')
      {
        countOCurrent++;

        if (countXCurrent >= 3)
        {
          countX[countXCurrent - 3]++; // Increment count for sequence length
        }

        countXCurrent = 0;
      }
      else
      {
        if (countOCurrent >= 3)
        {
          countO[countOCurrent - 3]++; // Increment count for sequence length
        }
        else if (countXCurrent >= 3)
        {
          countX[countXCurrent - 3]++; // Increment count for sequence length
        }

        countXCurrent = 0;
        countOCurrent = 0;
      }
    }
    // Final Pass
    if (countOCurrent >= 3)
    {
      countO[countOCurrent - 3]++; // Increment count for sequence length
    }
    else if (countXCurrent >= 3)
    {
      countX[countXCurrent - 3]++; // Increment count for sequence length
    }

    countXCurrent = 0;
    countOCurrent = 0;
  }
  *scoreX = 0, *scoreO = 0;

  // Check Vertically
  for (int j = 0; j < SIZE; j++)
  {
    int countXCurrent = 0, countOCurrent = 0;
    for (int i = 0; i < SIZE; i++)
    {
      if (board[i][j] == 'X')
      {
        countXCurrent++;

        if (countOCurrent >= 3)
        {
          countO[countOCurrent - 3]++; // Increment count for sequence length
        }

        countOCurrent = 0;
      }
      else if (board[i][j] == 'O')
      {
        countOCurrent++;

        if (countXCurrent >= 3)
        {
          countX[countXCurrent - 3]++; // Increment count for sequence length
        }

        countXCurrent = 0;
      }
      else
      {
        if (countOCurrent >= 3)
        {
          countO[countOCurrent - 3]++; // Increment count for sequence length
        }
        else if (countXCurrent >= 3)
        {
          countX[countXCurrent - 3]++; // Increment count for sequence length
        }

        countXCurrent = 0;
        countOCurrent = 0;
      }
    }
    // Final Pass
    if (countOCurrent >= 3)
    {
      countO[countOCurrent - 3]++; // Increment count for sequence length
    }
    else if (countXCurrent >= 3)
    {
      countX[countXCurrent - 3]++; // Increment count for sequence length
    }

    countXCurrent = 0;
    countOCurrent = 0;
  }

  // Check horizontally
  for (int i = 0; i < SIZE; i++)
  {

    int countXCurrent = 0, countOCurrent = 0;
    for (int j = 0; j < SIZE; j++)
    {
      if (board[i][j] == 'X')
      {

        countXCurrent++;
        countOCurrent = 0;
      }
      else if (board[i][j] == 'O')
      {
        countOCurrent++;
        countXCurrent = 0;
      }
      else
      {
        countXCurrent = 0;
        countOCurrent = 0;
      }
      if (countXCurrent == 3)
      {

        *scoreX += 3;
      }
      if (countXCurrent == 4)
      {
        *scoreX += 10;
        *scoreX -= 3;
      }
      if (countXCurrent == 5)
      {
        *scoreX += 25;
        *scoreX -= 10;
      }
      if (countXCurrent == 6)
      {
        *scoreX += 56;
        *scoreX -= 25;
      }
      if (countXCurrent == 7)
      {
        *scoreX += 119;
        *scoreX -= 56;
      }
      if (countOCurrent == 3)
      {

        *scoreO += 3;
      }
      if (countOCurrent == 4)
      {
        *scoreO += 10;
        *scoreO -= 3;
      }
      if (countOCurrent == 5)
      {
        *scoreO += 25;
        *scoreO -= 10;
      }
      if (countOCurrent == 6)
      {
        *scoreO += 56;
        *scoreO -= 25;
      }
      if (countXCurrent == 7)
      {
        *scoreO += 119;
        *scoreO -= 56;
      }
    }
  }

  // Check vertically
  for (int j = 0; j < SIZE; j++)
  {
    int countXCurrent = 0, countOCurrent = 0;
    for (int i = 0; i < SIZE; i++)
    {
      if (board[i][j] == 'X')
      {
        countXCurrent++;
        countOCurrent = 0;
      }
      else if (board[i][j] == 'O')
      {
        countOCurrent++;
        countXCurrent = 0;
      }
      else
      {
        countXCurrent = 0;
        countOCurrent = 0;
      }
      if (countXCurrent == 3)
      {

        *scoreX += 3;
      }
      if (countXCurrent == 4)
      {
        *scoreX += 10;
        *scoreX -= 3;
      }
      if (countXCurrent == 5)
      {
        *scoreX += 25;
        *scoreX -= 10;
      }
      if (countXCurrent == 6)
      {
        *scoreX += 56;
        *scoreX -= 25;
      }
      if (countXCurrent == 7)
      {
        *scoreX += 119;
        *scoreX -= 56;
      }
      if (countOCurrent == 3)
      {

        *scoreO += 3;
      }
      if (countOCurrent == 4)
      {
        *scoreO += 10;
        *scoreO -= 3;
      }
      if (countOCurrent == 5)
      {
        *scoreO += 25;
        *scoreO -= 10;
      }
      if (countOCurrent == 6)
      {
        *scoreO += 56;
        *scoreO -= 25;
      }
      if (countXCurrent == 7)
      {
        *scoreO += 119;
        *scoreO -= 56;
      }
    }
  }
}

void printScores(int countX[5], int countO[5], int scoreX, int scoreO)
{

  // Print breakdown of scores
  printf("\nBreakdown of Scores:\n");
  printf("Player X: ");
  for (int i = 0; i < 5; i++)
  {
    printf("%d sequence of %d, ", countX[i], i + 3);
    int sequencePosition = i + 3;
    // scoreX += countX[i] * ((sequencePosition == 3) ? 3 : (sequencePosition == 4) ? 10 : (sequencePosition == 5) ? 25 : (sequencePosition == 6) ? 56 : 119);
  }
  printf("\n");
  printf("Player O: ");
  for (int i = 0; i < 5; i++)
  {
    printf("%d sequence of %d, ", countO[i], i + 3);
    int sequencePosition = i + 3;
    // scoreO += countO[i] * ((sequencePosition == 3) ? 3 : (sequencePosition == 4) ? 10 : (sequencePosition == 5) ? 25 : (sequencePosition == 6) ? 56 : 119);
  }
  printf("\n");

  printf("Score for Player X: %d\n", scoreX);
  printf("Score for Player O: %d\n", scoreO);
}

void playGame(char board[SIZE][SIZE], char player1, char player2)
{
  char currentPlayer = player1;
  int moves = 0;
  int countX[5], countO[5];
  int scoreX = 0, scoreO = 0;
  // Initialize the board
  initializeBoard(board);

  // Main game loop
  int row = -1, col = -1;
  while (moves < SIZE * SIZE)
  {
    sleep(1);
    printf("\nCurrent Board:\n");
    printBoard(board);
    scoreBoard(board, countX, countO, &scoreX, &scoreO);
    printScores(countX, countO, scoreX, scoreO);

    row = -1;
    col = -1;
    playMove(board, currentPlayer, &row, &col);
    if (isValidMove(board, row, col))
    {
      board[row][col] = currentPlayer;
    }
    currentPlayer = (currentPlayer == player1) ? player2 : player1; // Switch player
    moves++;
  }

  // Game finished, calculate and print scores
  printf("\nFinal Board: \n");
  printBoard(board);
  scoreBoard(board, countX, countO, &scoreX, &scoreO);
  printScores(countX, countO, scoreX, scoreO);
}

int main()
{
  srand(time(NULL)); // Seed the random number generator

  // Run unit tests
  runUnitTests();

  char board[SIZE][SIZE], player1 = 'X', player2 = 'O';

  playGame(board, player1, player2);
  return 0;
}