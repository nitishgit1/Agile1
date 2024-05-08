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
// Function prototype
int evaluateMaxSequence(char board[SIZE][SIZE], int row, int col, char symbol);

// Your code

typedef struct
{
    int row; // Row of the move
    int col; // Column of the move
} Move;

int evaluateMove(char board[SIZE][SIZE], int row, int col, char player)
{
    char PLAYER_X = 'X'; // Character used for Player X
    char PLAYER_O = 'O'; // Character used for Player O
    char EMPTY_CELL = ' ';

    int score = 0;
    int directions[8][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}, {-1, 0}, {0, -1}, {-1, -1}, {-1, 1}};
    int lineLength;

    // Evaluates all eight possible directions from the given cell
    for (int i = 0; i < 8; i++)
    {
        lineLength = 1; // Start line length as 1 (the current cell)
        int dRow = directions[i][0];
        int dCol = directions[i][1];
        int tempRow = row + dRow;
        int tempCol = col + dCol;

        // Extend in the positive direction
        while (tempRow >= 0 && tempRow < SIZE && tempCol >= 0 && tempCol < SIZE && board[tempRow][tempCol] == player)
        {
            lineLength++;
            tempRow += dRow;
            tempCol += dCol;
        }

        // Reset and extend in the negative direction
        tempRow = row - dRow;
        tempCol = col - dCol;
        while (tempRow >= 0 && tempRow < SIZE && tempCol >= 0 && tempCol < SIZE && board[tempRow][tempCol] == player)
        {
            lineLength++;
            tempRow -= dRow;
            tempCol -= dCol;
        }

        // If a winning line is found, return a high score
        if (lineLength >= 4)
            return 1000;
        score += lineLength;
    }

    return score;
}

// Finds the best move for the given player
Move findBestMove(char board[SIZE][SIZE], char player)
{
    char PLAYER_X = 'X'; // Character used for Player X
    char PLAYER_O = 'O'; // Character used for Player O
    char EMPTY_CELL = ' ';

    Move bestMove = {0, 0};
    int bestScore = -1;

    // Iterate over all cells to find the best move
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (board[row][col] == EMPTY_CELL)
            {
                board[row][col] = player;
                int score = evaluateMove(board, row, col, player);
                board[row][col] = EMPTY_CELL;

                // Update the best move if a higher score is found
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove.row = row;
                    bestMove.col = col;
                }
            }
        }
    }

    return bestMove;
}

// Plays a move for a given player
void playMove(char board[SIZE][SIZE], char player, int *x, int *y)
{
    char PLAYER_X = 'X'; // Character used for Player X
    char PLAYER_O = 'O'; // Character used for Player O
    char EMPTY_CELL = ' ';

    if (player == PLAYER_X)
    {
        // Player X finds the best strategic move
        Move bestMove = findBestMove(board, PLAYER_X);
        printf("NEW strategy");
        *x = bestMove.row;
        *y = bestMove.col;
    }
    else if (player == PLAYER_O)
    {
        // Player O plays using a simulated approach with 1000 iterations
        Move bestMove = {0, 0};
        int bestScore = -1;
        int blockingMoveX = -1, blockingMoveY = -1;
        int maxBlockingScore = -1;
        bool foundBlockingMove = false;

        for (int i = 0; i < 1000; i++)
        {
            char boardCopy[SIZE][SIZE];
            memcpy(boardCopy, board, sizeof(char) * SIZE * SIZE);

            Move emptyCells[SIZE * SIZE];
            int numEmptyCells = 0;

            // Populate empty cells array
            for (int row = 0; row < SIZE; row++)
            {
                for (int col = 0; col < SIZE; col++)
                {
                    if (boardCopy[row][col] == EMPTY_CELL)
                    {
                        emptyCells[numEmptyCells].row = row;
                        emptyCells[numEmptyCells].col = col;
                        numEmptyCells++;
                    }
                }
            }

            if (numEmptyCells == 0) break;

            Move randomMove = emptyCells[rand() % numEmptyCells];
            int row = randomMove.row;
            int col = randomMove.col;

            boardCopy[row][col] = player;
            int score = evaluateMove(boardCopy, row, col, player);

//             // Keep track of the best move found through simulation
           if (score > bestScore) {
             bestScore = score;
             bestMove = randomMove;
                         }
            

        
       

        *x = bestMove.row;
        *y = bestMove.col;

            // Block opponent's sequence if it's greater than or equal to 3
            int maxSequenceOpponent = evaluateMaxSequence(boardCopy, row, col, PLAYER_X);
            if (maxSequenceOpponent >= 5)
            {
                Move randomMove = emptyCells[rand() % numEmptyCells];
                int row = randomMove.row;
                int col = randomMove.col;
                if (boardCopy[row][col] != PLAYER_O && boardCopy[row][col] == EMPTY_CELL)
                {
                    *x =row;
                    *y  =col;
                    // printf("got a block move\n");
                    // printf("playing blocked move at %d %d",row,col);
                    break;

                }
            }
        }

    }
}
                      

int evaluateMaxSequence(char board[SIZE][SIZE], int row, int col, char symbol)
{
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    int maxSequence = 0;

    // Check each direction for potential sequences
    for (int d = 0; d < 4; d++)
    {
        int dx = directions[d][0];
        int dy = directions[d][1];
        int sequence = 1;

        // Count symbols in one direction
        for (int i = 1; i < 5; i++)
        {
            int newRow = row + i * dx;
            int newCol = col + i * dy;

            // Check if within bounds
            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE)
            {
                if (board[newRow][newCol] == symbol)
                {
                    sequence++;
                }
                else
                {
                    break; // End of sequence
                }
            }
            else
            {
                break; // Out of bounds
            }
        }

        // Update maxSequence if necessary
        if (sequence > maxSequence)
        {
            maxSequence = sequence;
        }
    }

    return maxSequence;
}
